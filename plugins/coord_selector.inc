<?php

$plugin = array(
  'form'     => 'coord_tamper_form',
  'callback' => 'coord_tamper_callback',
  'name'     => 'Coordinates selector',
  'multi'    => 'direct',
  'category' => 'Other',
);

function coord_tamper_form($importer, $element_key, $settings) {
  $form = array();

  $form['instructions'] = array(
    '#markup' => t('Expected input: a string with lat,lon')
  );

  $form['coord_selector'] = array(
    '#type' => 'select',
    '#title' => t('Lat or lon'),
    '#options' => array(
        0 => t('Lat'),
        1 => t('Lon'),
    ),
    '#default_value' => isset($settings['coord_selector']) ? $settings['coord_selector'] : '',
    '#description' => t('Select lat or lon value.'),
  );

  return $form;
}

function coord_tamper_callback($source, $item_key, $element_key, &$field, $settings) {
  if (!is_array($field)) {
    $field = array($field);
  }

  $out = array();

  foreach ($field as $f) {
    if(is_array($f)) {
      $count = count($f);
      if ($count > 0 && isset($f[$settings['coord_selector']])) {
        $out[] = $f[$settings['coord_selector']];
      } else {
        $out[] = '';
      }
    } else {
      $f = explode(',', $f);
      $count = count($f);
      if ($count > 0 && isset($f[$settings['coord_selector']])) {
        $out[] = $f[$settings['coord_selector']];
      } else {
        $out[] = '';
      }
    }
  }
  
  if (count($out) == 1) {
    $out = $out[0];
  }
  $field = $out;
}
