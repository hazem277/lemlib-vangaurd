#include "graphics.h" // IWYU pragma: keep
#include "auton.h"
#include "liblvgl/core/lv_disp.h"
#include "liblvgl/core/lv_obj.h"
#include "liblvgl/core/lv_obj_style.h"
#include "liblvgl/misc/lv_color.h"
#include "liblvgl/widgets/lv_btn.h" // IWYU pragma: keep
#include "main.h"                   // IWYU pragma: keep
#include <atomic>

std::atomic<bool> recordingPID(true); // atomic to ensure thread-safety
const int maxData = 1000;

static lv_obj_t *chart;
/* Source:
 * https://github.com/ankur219/ECG-Arrhythmia-classification/blob/642230149583adfae1e4bd26c6f0e1fd8af2be0e/sample.csv*/
static lv_coord_t ecg_sample[maxData] = {0};

void recordPID() {
  recordingPID = true;
  int dataPoint = 0;
  while (recordingPID && dataPoint < maxData) {
    ecg_sample[dataPoint] = (static_cast<lv_coord_t>(chassis.getPose().theta));
    dataPoint++;
  }
  recordingPID = false;
  std::cout << "\nnumber of data points: " << dataPoint << std::endl;
}

void stopRecordingPID() { recordingPID = false; }

static void slider_x_event_cb(lv_event_t *e) {
  lv_obj_t *obj = lv_event_get_target(e);
  int32_t v = lv_slider_get_value(obj);
  lv_chart_set_zoom_x(chart, v);
}

static void slider_y_event_cb(lv_event_t *e) {
  lv_obj_t *obj = lv_event_get_target(e);
  int32_t v = lv_slider_get_value(obj);
  lv_chart_set_zoom_y(chart, v);
}

/**
 * Display 1000 data points with zooming and scrolling.
 * See how the chart changes drawing mode (draw only vertical lines) when
 * the points get too crowded.
 */
void lv_example_chart_5(void) {
  /*Create a chart*/
  chart = lv_chart_create(lv_scr_act());
  lv_obj_set_size(chart, 200, 150);
  lv_obj_align(chart, LV_ALIGN_CENTER, -30, -30);
  lv_chart_set_range(chart, LV_CHART_AXIS_PRIMARY_Y, -1000, 1000);

  /*Do not display points on the data*/
  lv_obj_set_style_size(chart, 0, LV_PART_INDICATOR);

  lv_chart_series_t *ser = lv_chart_add_series(
      chart, lv_palette_main(LV_PALETTE_RED), LV_CHART_AXIS_PRIMARY_Y);

  uint32_t pcnt = sizeof(ecg_sample) / sizeof(ecg_sample[0]);
  lv_chart_set_point_count(chart, pcnt);
  lv_chart_set_ext_y_array(chart, ser, (lv_coord_t *)ecg_sample);

  lv_obj_t *slider;
  slider = lv_slider_create(lv_scr_act());
  lv_slider_set_range(slider, LV_IMG_ZOOM_NONE, LV_IMG_ZOOM_NONE * 10);
  lv_obj_add_event_cb(slider, slider_x_event_cb, LV_EVENT_VALUE_CHANGED, NULL);
  lv_obj_set_size(slider, 200, 10);
  lv_obj_align_to(slider, chart, LV_ALIGN_OUT_BOTTOM_MID, 0, 20);

  slider = lv_slider_create(lv_scr_act());
  lv_slider_set_range(slider, LV_IMG_ZOOM_NONE, LV_IMG_ZOOM_NONE * 10);
  lv_obj_add_event_cb(slider, slider_y_event_cb, LV_EVENT_VALUE_CHANGED, NULL);
  lv_obj_set_size(slider, 10, 150);
  lv_obj_align_to(slider, chart, LV_ALIGN_OUT_RIGHT_MID, 20, 0);
}

lv_obj_t *screenDebug = lv_obj_create(NULL);
void lv_example_img_1(void)
{
    LV_IMG_DECLARE(img_cogwheel_argb);
    lv_obj_t * img1 = lv_img_create(screenDebug);
    lv_img_set_src(img1, &img_cogwheel_argb);
    lv_obj_align(img1, LV_ALIGN_CENTER, 0, -20);
    lv_obj_set_size(img1, 200, 200);

    lv_obj_t * img2 = lv_img_create(screenDebug);
    lv_obj_align_to(img2, img1, LV_ALIGN_OUT_BOTTOM_MID, 0, 20);
}

lv_obj_t *buttonRedPos = lv_btn_create(lv_scr_act());
lv_obj_t *buttonRedNeg = lv_btn_create(lv_scr_act());
lv_obj_t *buttonBluePos = lv_btn_create(lv_scr_act());
lv_obj_t *buttonBlueNeg = lv_btn_create(lv_scr_act());
lv_obj_t *buttonScoreAlliance = lv_btn_create(lv_scr_act());
lv_obj_t *buttonSkills = lv_btn_create(lv_scr_act());
lv_obj_t *buttonConfirm = lv_btn_create(lv_scr_act());

int width = 120;
int height = 70;
int xPos = -160;
int yPos = -70;

void autonSelector(void) {
  lv_obj_t *label;

  /*
  Red Positive
  */
  lv_obj_add_event_cb(
      buttonRedPos,
      [](lv_event_t *e) {
        lv_obj_add_state(buttonRedPos, LV_STATE_DISABLED);
        lv_obj_clear_state(buttonRedNeg, LV_STATE_DISABLED);
        lv_obj_clear_state(buttonBluePos, LV_STATE_DISABLED);
        lv_obj_clear_state(buttonBlueNeg, LV_STATE_DISABLED);
        lv_obj_clear_state(buttonSkills, LV_STATE_DISABLED);
        autonType = RED_POSITIVE;
      },
      LV_EVENT_PRESSED, NULL);
  lv_obj_align(buttonRedPos, LV_ALIGN_CENTER, xPos, yPos);
  lv_obj_set_size(buttonRedPos, width, height);

  lv_obj_set_style_radius(buttonRedPos, 2, 0);
  lv_obj_set_style_bg_color(buttonRedPos, lv_palette_main(LV_PALETTE_RED),
                            LV_STATE_DEFAULT);
  lv_obj_set_style_bg_color(buttonRedPos, lv_palette_darken(LV_PALETTE_RED, 3),
                            LV_STATE_DISABLED);

  label = lv_label_create(buttonRedPos);
  lv_label_set_text(label, "Red Positive");
  lv_obj_center(label);

  /*
  Red Negative
  */
  lv_obj_add_event_cb(
      buttonRedNeg,
      [](lv_event_t *e) {
        lv_obj_add_state(buttonRedNeg, LV_STATE_DISABLED);
        lv_obj_clear_state(buttonRedPos, LV_STATE_DISABLED);
        lv_obj_clear_state(buttonBluePos, LV_STATE_DISABLED);
        lv_obj_clear_state(buttonBlueNeg, LV_STATE_DISABLED);
        lv_obj_clear_state(buttonSkills, LV_STATE_DISABLED);
        autonType = RED_NEGATIVE;
      },
      LV_EVENT_PRESSED, NULL);
  lv_obj_align(buttonRedNeg, LV_ALIGN_CENTER, xPos + 130, yPos);
  lv_obj_set_size(buttonRedNeg, width, height);

  lv_obj_set_style_radius(buttonRedNeg, 2, 0);
  lv_obj_set_style_bg_color(buttonRedNeg, lv_palette_main(LV_PALETTE_RED),
                            LV_STATE_DEFAULT);
  lv_obj_set_style_bg_color(buttonRedNeg, lv_palette_darken(LV_PALETTE_RED, 3),
                            LV_STATE_DISABLED);

  label = lv_label_create(buttonRedNeg);
  lv_label_set_text(label, "Red Negative");
  lv_obj_center(label);

  /*
  Blue Positive
  */
  lv_obj_add_event_cb(
      buttonBluePos,
      [](lv_event_t *e) {
        lv_obj_add_state(buttonBluePos, LV_STATE_DISABLED);
        lv_obj_clear_state(buttonBlueNeg, LV_STATE_DISABLED);
        lv_obj_clear_state(buttonRedPos, LV_STATE_DISABLED);
        lv_obj_clear_state(buttonRedNeg, LV_STATE_DISABLED);
        lv_obj_clear_state(buttonSkills, LV_STATE_DISABLED);
        autonType = BLUE_POSITIVE;
      },
      LV_EVENT_PRESSED, NULL);
  lv_obj_align(buttonBluePos, LV_ALIGN_CENTER, xPos, yPos + 80);
  lv_obj_set_size(buttonBluePos, width, height);

  lv_obj_set_style_radius(buttonBluePos, 2, 0);

  label = lv_label_create(buttonBluePos);
  lv_label_set_text(label, "Blue Positive");
  lv_obj_center(label);

  /*
  Score Alliance Stake
  */
  lv_obj_add_event_cb(
      buttonBlueNeg,
      [](lv_event_t *e) {
        lv_obj_add_state(buttonBlueNeg, LV_STATE_DISABLED);
        lv_obj_clear_state(buttonBluePos, LV_STATE_DISABLED);
        lv_obj_clear_state(buttonRedPos, LV_STATE_DISABLED);
        lv_obj_clear_state(buttonRedNeg, LV_STATE_DISABLED);
        lv_obj_clear_state(buttonSkills, LV_STATE_DISABLED);
        autonType = BLUE_NEGATIVE;
      },
      LV_EVENT_PRESSED, NULL);
  lv_obj_align(buttonBlueNeg, LV_ALIGN_CENTER, xPos + 130, yPos + 80);
  lv_obj_set_size(buttonBlueNeg, width, height);

  lv_obj_set_style_radius(buttonBlueNeg, 2, 0);

  label = lv_label_create(buttonBlueNeg);
  lv_label_set_text(label, "Blue Negative");
  lv_obj_center(label);

  lv_obj_add_event_cb(
      buttonScoreAlliance,
      [](lv_event_t *e) {
        scoreAllianceStake = !scoreAllianceStake;
      },
      LV_EVENT_ALL, NULL);
  lv_obj_align(buttonScoreAlliance, LV_ALIGN_CENTER, xPos + 290, yPos + 40);
  lv_obj_set_size(buttonScoreAlliance, width + 60, (height * 2) + 10);
  lv_obj_add_flag(buttonScoreAlliance, LV_OBJ_FLAG_CHECKABLE);

  lv_obj_set_style_radius(buttonScoreAlliance, 2, 0);
  lv_obj_set_style_bg_color(
      buttonScoreAlliance, lv_palette_main(LV_PALETTE_GREEN), LV_STATE_DEFAULT);
  lv_obj_set_style_bg_color(buttonScoreAlliance,
                            lv_palette_main(LV_PALETTE_GREY), LV_STATE_CHECKED);

  label = lv_label_create(buttonScoreAlliance);
  lv_label_set_text(label, "Alliance Stake");
  lv_obj_center(label);

  /*
  Skills
  */
  lv_obj_add_event_cb(
      buttonSkills,
      [](lv_event_t *e) {
        lv_obj_add_state(buttonSkills, LV_STATE_DISABLED);
        lv_obj_clear_state(buttonRedPos, LV_STATE_DISABLED);
        lv_obj_clear_state(buttonRedNeg, LV_STATE_DISABLED);
        lv_obj_clear_state(buttonBluePos, LV_STATE_DISABLED);
        lv_obj_clear_state(buttonBlueNeg, LV_STATE_DISABLED);
        autonType = SKILLS;
      },
      LV_EVENT_PRESSED, NULL);
  lv_obj_align(buttonSkills, LV_ALIGN_CENTER, xPos + 65, yPos + 155);
  lv_obj_set_size(buttonSkills, (width * 2) + 10, 60);

  lv_obj_set_style_radius(buttonSkills, 2, 0);
  lv_obj_set_style_bg_color(buttonSkills, lv_palette_main(LV_PALETTE_AMBER),
                            LV_STATE_DEFAULT);

  label = lv_label_create(buttonSkills);
  lv_label_set_text(label, "Skill Run");
  lv_obj_center(label);

  /*
  Skills
  */
  lv_obj_add_event_cb(
    buttonConfirm,
    [](lv_event_t *e) {
      if(autonType != NONE) {
        autonConfirmed = true;
        // lv_example_img_1();
        debugTabs();
        lv_scr_load_anim(screenDebug, LV_SCR_LOAD_ANIM_FADE_ON, 250, 1000, false);
      }
    },
    LV_EVENT_PRESSED, NULL);
lv_obj_align(buttonConfirm, LV_ALIGN_CENTER, xPos + 290, yPos + 155);
lv_obj_set_size(buttonConfirm, width + 60, 60);

lv_obj_set_style_radius(buttonConfirm, 2, 0);
lv_obj_set_style_bg_color(buttonConfirm, lv_palette_main(LV_PALETTE_LIGHT_GREEN),
                          LV_STATE_DEFAULT);

label = lv_label_create(buttonConfirm);
lv_label_set_text(label, "Confirm");
lv_obj_center(label);
}

void debugTabs(void)
{
    /*Create a Tab view object*/
    lv_obj_t * tabview;
    tabview = lv_tabview_create(screenDebug, LV_DIR_LEFT, 80);

    lv_obj_set_style_bg_color(tabview, lv_palette_lighten(LV_PALETTE_RED, 2), 0);

    lv_obj_t * tab_btns = lv_tabview_get_tab_btns(tabview);
    lv_obj_set_style_bg_color(tab_btns, lv_palette_darken(LV_PALETTE_GREY, 3), 0);
    lv_obj_set_style_text_color(tab_btns, lv_palette_lighten(LV_PALETTE_GREY, 5), 0);
    lv_obj_set_style_border_side(tab_btns, LV_BORDER_SIDE_RIGHT, LV_STATE_CHECKED);

    /*Add 3 tabs (the tabs are page (lv_page) and can be scrolled*/
    lv_obj_t * tab1 = lv_tabview_add_tab(tabview, "Tab 1");
    lv_obj_t * tab2 = lv_tabview_add_tab(tabview, "Tab 2");
    lv_obj_t * tab3 = lv_tabview_add_tab(tabview, "Tab 3");
    lv_obj_t * tab4 = lv_tabview_add_tab(tabview, "Tab 4");
    lv_obj_t * tab5 = lv_tabview_add_tab(tabview, "Tab 5");

    lv_obj_set_style_bg_color(tab2, lv_palette_lighten(LV_PALETTE_AMBER, 3), 0);
    lv_obj_set_style_bg_opa(tab2, LV_OPA_COVER, 0);

    /*Add content to the tabs*/
    lv_obj_t * label = lv_label_create(tab1);
    lv_label_set_text(label, "First tab");

    label = lv_label_create(tab2);
    lv_label_set_text(label, "Second tab");

    label = lv_label_create(tab3);
    lv_label_set_text(label, "Third tab");

    label = lv_label_create(tab4);
    lv_label_set_text(label, "Forth tab");

    label = lv_label_create(tab5);
    lv_label_set_text(label, "Fifth tab");

    lv_obj_clear_flag(lv_tabview_get_content(tabview), LV_OBJ_FLAG_SCROLLABLE);
}
