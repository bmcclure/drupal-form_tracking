<?php

/**
 * @file
 * Admin settings for commerce_tax_services.
 *
 * Copyright (C) Alexander Bischoff, adTumbler.com
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 */

/**
 * Admin settings menu callback.
 * @param $form
 * @param $form_state
 * @return mixed
 */
function form_tracking_admin_settings($form, &$form_state) {
  $form['options'] = form_tracking_admin_options();
  $form['forms'] = form_tracking_admin_forms();

  drupal_alter('form_tracking_admin_options', $form, $form_state);

  return system_settings_form($form);
}

function form_tracking_admin_forms() {
  $forms = array(
    '#type' => 'container',
    '#prefix' => '<div id="form_tracking_forms">',
    '#suffix' => '</div>',
    '#tree' => FALSE,
  );

  $info = form_tracking_form_type_info();

  $hook = 'form_tracking_forms';

  foreach ($info as $form_type_id => $form_type_info) {
    if (!empty($form_type_info['module'])) {
      if (module_hook($form_type_info['module'], $hook)) {
        $id = "form_tracking_enabled_forms_$form_type_id";

        $forms[$id] = array(
          '#type' => 'checkboxes',
          '#title' => t('Forms of type: @name', array('@name' => $form_type_info['name'])),
          '#description' => t('Select the @name forms to enable form tracking for.', array('@name' => $form_type_info['name'])),
          '#default_value' => variable_get($id),
          '#options' => module_invoke($form_type_info['module'], $hook),
        );
      }
    }
  }

  return $forms;
}

function form_tracking_admin_options() {
  $options = array(
    '#type' => 'container',
    '#prefix' => '<div id="commerce_tax_services_options">',
    '#suffix' => '</div>',
    '#tree' => FALSE,
  );

  $options['form_tracking_enabled'] = [
    '#type' => 'checkbox',
    '#title' => 'Enable form tracking',
    '#description' => t('Unchecking this will turn off form tracking globally.'),
    '#default_value' => variable_get('form_tracking_enabled'),
  ];

  return $options;
}
