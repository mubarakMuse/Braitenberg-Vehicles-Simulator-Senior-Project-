/**
 * @file graphics_arena_viewer.cc
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <vector>
#include <iostream>

#include "src/graphics_arena_viewer.h"
#include "src/arena_params.h"
#include "src/rgb_color.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Constructors/Destructor
 ******************************************************************************/
GraphicsArenaViewer::GraphicsArenaViewer(
    const struct arena_params *const params,
    Arena * arena, Controller * controller) :
    GraphicsApp(
        params->x_dim + GUI_MENU_WIDTH + GUI_MENU_GAP * 2,
        params->y_dim,
        "Robot Simulation"),
    controller_(controller),
    arena_(arena) {
  auto *gui = new nanogui::FormHelper(screen());
  nanogui::ref<nanogui::Window> window =
      gui->addWindow(
          Eigen::Vector2i(10 + GUI_MENU_GAP, 10),
          "Menu");
  // vvvvvvvvvvvv    ADDED THIS ONE LINE to register the window  vvvvvvvvvvvv
  // gui->addGroup creates a heading within the window
  window->setLayout(new nanogui::GroupLayout());

  gui->addGroup("Simulation Control");
  playing_button_ =
    gui->addButton(
      "Play",
      std::bind(&GraphicsArenaViewer::OnPlayingBtnPressed, this));
    playing_button_->setFixedWidth(100);
    
    NewGame_button_ =
    gui->addButton(
      "NewGame",
      std::bind(&GraphicsArenaViewer::NewGameBtnPressed, this));
    NewGame_button_->setFixedWidth(100);
  gui->addGroup("Arena Configuration");
   // Creating a panel impacts the layout. Widgets, sliders, buttons can be
  // assigned to either the window or the panel.
  nanogui::Widget *panel = new nanogui::Widget(window);

  // *************** SLIDER 1 ************************//
  new nanogui::Label(panel, "Number of Robots", "sans-bold");
  nanogui::Slider *slider = new nanogui::Slider(panel);
  // The starting value (range is from 0 to 1)
  // Note that below the displayed value is 10* slider value.
  slider->setValue(0.5f);
  slider->setFixedWidth(100);
  
  // Display the corresponding value of the slider in this textbox
  nanogui::TextBox *textBox = new nanogui::TextBox(panel);
  textBox->setFixedSize(nanogui::Vector2i(60, 25));
  textBox->setFontSize(20);
  textBox->setValue("5");

  // This is the lambda function called while the user is moving the slider
  slider->setCallback(
    [textBox](float value) {
      textBox->setValue(std::to_string(int(value*10)));
    }
  );
  // This is the lambda function called once the user is no longer manipulating the slider.
  // Note robot_count_ is set, which is a graphics_arena_ variable in this version, although
  // you should communicate that value to the controller so that it can configure the Arena.
  slider->setFinalCallback(
    [&](float value) {
      int robot_count_ = int(value*10);
      std::cout << "Final slider value: " << value;
      std::cout << " \n robot " << robot_count_ << std::endl;
    }
  );

  // *************** SLIDER 2 ************************//
  new nanogui::Label(panel, "Number of Lights", "sans-bold");
  nanogui::Slider *slider2 = new nanogui::Slider(panel);
  slider2->setValue(0.0f);
  slider2->setFixedWidth(100);
  //textBox->setUnits("%");

  nanogui::TextBox *textBox2 = new nanogui::TextBox(panel);
  textBox2->setFixedSize(nanogui::Vector2i(60, 25));
  textBox2->setFontSize(20);
  textBox2->setValue("0");
  //textBox2->setAlignment(nanogui::TextBox::Alignment::Right);

  slider2->setCallback(
    [textBox2](float value) {
      textBox2->setValue(std::to_string(int(value*5)));
    }
  );

  slider2->setFinalCallback(
    [&](float value) {
      int robot_count_ = int(value*5);
      std::cout << "Final slider2 value: " << value;
      std::cout << " robot " << robot_count_ << std::endl;
    }
  );

  // Lays out all the components with "15" units of inbetween spacing
  panel->setLayout(new nanogui::BoxLayout(nanogui::Orientation::Vertical, nanogui::Alignment::Middle, 0, 15));

  // ^^^^^^^^^^^^^^^^^^^^^^    ADDED TO HERE (modification of nanogui example1.cc)  ^^^^^^^^^^^^^^^^^^^^^^^^

  screen()->performLayout();
}

/*******************************************************************************
 * Member Functions
 ******************************************************************************/

// This is the primary driver for state change in the arena.
// It will be called at each iteration of nanogui::mainloop()
// except when the game is paused.
void GraphicsArenaViewer::UpdateSimulation(double dt) {
  if (!paused_) {
    controller_->AdvanceTime(dt);
  }
}

/*******************************************************************************
 * Handlers for User Keyboard and Mouse Events
 ******************************************************************************/
void GraphicsArenaViewer::OnPlayingBtnPressed() {
  // is the playing_button_ is clicked it play
  // and the bool switched to false and vice versa game starts of as paused
  if (!paused_) {
    paused_ = true;
    playing_button_->setCaption("Play");
  } else {
    paused_ = false;
    playing_button_->setCaption("Pause");
  }
}
void GraphicsArenaViewer::NewGameBtnPressed() {
  // handles the newgame which communicates to the arena to reset.
  paused_ = true;
  playing_button_->setCaption("Play");
  controller_->AcceptCommunication(kNewGame);
}
  // OnSpecialKeyDown is called when the user presses down on one of the
  // special keys (e.g. the arrow keys).
void GraphicsArenaViewer::OnSpecialKeyDown(int key,
  __unused int scancode, __unused int modifiers) {
    Communication key_value = kNone;
    switch (key) {
      case GLFW_KEY_LEFT:
      controller_->AcceptCommunication(kKeyLeft);
        break;
      case GLFW_KEY_RIGHT:
      controller_->AcceptCommunication(kKeyRight);
        break;
      case GLFW_KEY_UP:
      controller_->AcceptCommunication(kKeyUp);
        break;
      case GLFW_KEY_DOWN:
      controller_->AcceptCommunication(kKeyDown);
        break;
      default: {}
    }
  controller_->AcceptCommunication(key_value);
}

/*******************************************************************************
 * Drawing of Entities in Arena
 ******************************************************************************/
void GraphicsArenaViewer::DrawRobot(NVGcontext *ctx,
                                     const Robot *const robot) {
  // translate and rotate all graphics calls that follow so that they are
  // centered, at the position and heading of this robot
  nvgSave(ctx);
  nvgTranslate(ctx,
               static_cast<float>(robot->get_pose().x),
               static_cast<float>(robot->get_pose().y));
  nvgRotate(ctx,
            static_cast<float>(robot->get_pose().theta * M_PI / 180.0));

  // robot's circle
  nvgBeginPath(ctx);
  nvgCircle(ctx, 0.0, 0.0, static_cast<float>(robot->get_radius()));
  nvgFillColor(ctx,
               nvgRGBA(robot->get_color().r, robot->get_color().g,
                       robot->get_color().b, 255));
  nvgFill(ctx);
  nvgStrokeColor(ctx, nvgRGBA(0, 0, 0, 255));
  nvgStroke(ctx);

  // robot id text label
  nvgSave(ctx);
  nvgRotate(ctx, static_cast<float>(M_PI / 2.0));
  nvgFillColor(ctx, nvgRGBA(0, 0, 0, 255));
  nvgText(ctx, 0.0, 10.0, robot->get_name().c_str(), nullptr);
  nvgRestore(ctx);
  nvgRestore(ctx);
}
void GraphicsArenaViewer::DrawArena(NVGcontext *ctx) {
  nvgBeginPath(ctx);
  // Creates new rectangle shaped sub-path.
  nvgRect(ctx, 0, 0, arena_->get_x_dim(), arena_->get_y_dim());
  nvgStrokeColor(ctx, nvgRGBA(255, 255, 255, 255));
  nvgStroke(ctx);
}

void GraphicsArenaViewer::DrawEntity(NVGcontext *ctx,
                                       const ArenaEntity *const entity) {
  // Light's circle
  nvgBeginPath(ctx);
  nvgCircle(ctx,
            static_cast<float>(entity->get_pose().x),
            static_cast<float>(entity->get_pose().y),
            static_cast<float>(entity->get_radius()));
  nvgFillColor(ctx,
               nvgRGBA(entity->get_color().r, entity->get_color().g,
                       entity->get_color().b, 255));
  nvgFill(ctx);
  nvgStrokeColor(ctx, nvgRGBA(0, 0, 0, 255));
  nvgStroke(ctx);

  // Light id text label
  nvgFillColor(ctx, nvgRGBA(0, 0, 0, 255));
  nvgText(ctx,
          static_cast<float>(entity->get_pose().x),
          static_cast<float>(entity->get_pose().y),
          entity->get_name().c_str(), nullptr);
}

void GraphicsArenaViewer::DrawUsingNanoVG(NVGcontext *ctx) {
  // initialize text rendering settings
  nvgFontSize(ctx, 18.0f);
  nvgFontFace(ctx, "sans-bold");
  nvgTextAlign(ctx, NVG_ALIGN_CENTER | NVG_ALIGN_MIDDLE);
  DrawArena(ctx);
  std::vector<ArenaEntity *> entities = arena_->get_entities();
  for (auto &entity : entities) {
    DrawEntity(ctx, entity);
  } /* for(i..) */
}

NAMESPACE_END(csci3081);
