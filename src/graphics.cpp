#include "graphics.h" // IWYU pragma: keep
#include "auton/auton.h"
#include "liblvgl/core/lv_disp.h"
#include "liblvgl/core/lv_obj.h"
#include "liblvgl/core/lv_obj_style.h"
#include "liblvgl/misc/lv_color.h"
#include "liblvgl/widgets/lv_btn.h" // IWYU pragma: keep
#include "main.h"                   // IWYU pragma: keep

lv_obj_t *screenAutonSelector = lv_obj_create(NULL);
lv_obj_t *screenLogo = lv_obj_create(NULL);
lv_obj_t *screenDebug = lv_obj_create(NULL);

lv_obj_t *buttonRedPos = lv_btn_create(screenAutonSelector);
lv_obj_t *buttonRedNeg = lv_btn_create(screenAutonSelector);
lv_obj_t *buttonBluePos = lv_btn_create(screenAutonSelector);
lv_obj_t *buttonBlueNeg = lv_btn_create(screenAutonSelector);
lv_obj_t *buttonScoreAlliance = lv_btn_create(screenAutonSelector);
lv_obj_t *buttonSkills = lv_btn_create(screenAutonSelector);
lv_obj_t *buttonConfirm = lv_btn_create(screenAutonSelector);

int width = 120;
int height = 70;
int xPos = -160;
int yPos = -70;

// lv_obj_t *imgVanguardLogo;
// LV_IMG_DECLARE(vangaurd480x240px);

void autonSelector(void) {
  lv_obj_t *label;
  lv_scr_load_anim(screenAutonSelector, LV_SCR_LOAD_ANIM_FADE_IN, 250, 1000, false);

  // imgVanguardLogo = lv_img_create(screenLogo);
  // lv_img_set_src(imgVanguardLogo, &vangaurd480x240px);
  // lv_obj_set_size(imgVanguardLogo, 480, 240);
  // lv_obj_align(imgVanguardLogo, LV_ALIGN_CENTER, 0, 0);

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
      [](lv_event_t *e) { scoreAllianceStake = !scoreAllianceStake; },
      LV_EVENT_PRESSED, NULL);
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
        if (autonType != NONE) {
          chassis.calibrate();
          autonConfirmed = true;
          lv_scr_load_anim(screenLogo, LV_SCR_LOAD_ANIM_FADE_ON, 250, 1000,
                           false);
        }
      },
      LV_EVENT_PRESSED, NULL);
  lv_obj_align(buttonConfirm, LV_ALIGN_CENTER, xPos + 290, yPos + 155);
  lv_obj_set_size(buttonConfirm, width + 60, 60);

  lv_obj_set_style_radius(buttonConfirm, 2, 0);
  lv_obj_set_style_bg_color(
      buttonConfirm, lv_palette_main(LV_PALETTE_LIGHT_GREEN), LV_STATE_DEFAULT);

  label = lv_label_create(buttonConfirm);
  lv_label_set_text(label, "Confirm");
  lv_obj_center(label);

  debugTabs();
}

void debugTabs(void) {
  /*Create a Tab view object*/
  lv_obj_t *tabview;
  tabview = lv_tabview_create(screenDebug, LV_DIR_LEFT, 80);

  lv_obj_set_style_bg_color(tabview, lv_palette_lighten(LV_PALETTE_RED, 2), 0);

  lv_obj_t *tab_btns = lv_tabview_get_tab_btns(tabview);
  lv_obj_set_style_bg_color(tab_btns, lv_palette_darken(LV_PALETTE_GREY, 3), 0);
  lv_obj_set_style_text_color(tab_btns, lv_palette_lighten(LV_PALETTE_GREY, 5),
                              0);
  lv_obj_set_style_border_side(tab_btns, LV_BORDER_SIDE_RIGHT,
                               LV_STATE_CHECKED);

  /*Add 3 tabs (the tabs are page (lv_page) and can be scrolled*/
  lv_obj_t *tab1 = lv_tabview_add_tab(tabview, "Tab 1");
  lv_obj_t *tab2 = lv_tabview_add_tab(tabview, "Tab 2");
  lv_obj_t *tab3 = lv_tabview_add_tab(tabview, "Tab 3");
  lv_obj_t *tab4 = lv_tabview_add_tab(tabview, "Tab 4");
  lv_obj_t *tab5 = lv_tabview_add_tab(tabview, "Tab 5");

  lv_obj_set_style_bg_color(tab2, lv_palette_lighten(LV_PALETTE_AMBER, 3), 0);
  lv_obj_set_style_bg_opa(tab2, LV_OPA_COVER, 0);

  /*Add content to the tabs*/
  lv_obj_t *label = lv_label_create(tab1);
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
