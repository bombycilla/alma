<?php


/**
 * @file
 * Ding debt plugin.
 */

$plugin = array(
  'description' => t('Alma debt plugin'),
  'version' => 1,
);

/**
 *
 */
function alma_user_debt_settings_form() {
  $form['description'] = array(
    '#type' => 'markup',
    '#value' => t("Ding Dibs Integration module is required for payments."),
  );

  $form['status'] = array(
    '#type' => 'item',
    '#title' => t('Payments'),
    '#value' => function_exists('ding_dibs_payment_prepare') ? t('Enabled') : t('Disabled'),
  );

  return $form;
}

/**
 */
function alma_user_debt_list($account) {
  $return = array();
  $creds = ding_library_user_get_credentials($account);
  if ($creds != DING_PROVIDER_AUTH_REQUIRED) {
    $debts = alma_client_invoke('get_debts', $creds['user_id'], $creds['password']);
    if ($debts && isset($debts['debts'])) {
      foreach ($debts['debts'] as $id => $debt) {
        $return[$id] = array(
          'id' => $id,
          'display_title' => alma_debt_types($debt['type']) . ($debt['note'] ? ' (' . $debt['note'] . ')' : ""),
          'payable' => TRUE,
          'date' => $debt['date'],
          'amount' => $debt['amount'],
        );
      }
    }
  }
  return $return;
}

function alma_debt_types($debttype) {
  switch ($debttype):
    case 'overdueFeeInvoiceDebt': 
        return t('overdue Fee Invoice Debt');
    case 'overdueFeeDebt': 
        return t('overdue Fee Debt');
    case 'loanFeeDebt': 
        return t('loan Fee Debt');
    case 'reservationPickupFeeDebt': 
        return t('reservation Pickup Fee Debt');
    case 'reservationFeeDebt': 
        return t('reservation Fee Debt');
    case 'deleteReservationFeeDebt': 
        return t('delete Reservation Fee Debt');
    case 'illFeeDebt': 
        return t('ill Fee Debt');
    case 'smsReservationFeeDebt': 
        return t('sms Reservation Fee Debt');
    case 'smsReminderFeeDebt': 
        return t('sms Reminder Fee Debt');
    case 'smsRecall1FeeDebt': 
        return t('sms Recall 1. Fee Debt');
    case 'smsRecall2FeeDebt': 
        return t('sms Recall 2. Fee Debt');
    case 'smsRecall3FeeDebt': 
        return t('sms Recall 3. Fee Debt');
    case 'smsRecall4FeeDebt': 
        return t('sms Recall 4. Fee Debt');
    case 'smsRecall5FeeDebt': 
        return t('sms Recall 5. Fee Debt');
    case 'emailReminderFeeDebt': 
        return t('email Reminder Fee Debt');
    case 'otherFeeDebt': 
        return t('other Fee Debt');
    default: 
        return t($debttype);
  endswitch;
}
