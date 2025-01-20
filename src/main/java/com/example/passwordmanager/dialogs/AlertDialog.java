package com.example.passwordmanager.dialogs;

import javafx.scene.control.Alert;

public class AlertDialog {

    public static void showPopUp(Alert.AlertType alertType, String windowTitle, String titleText, String contentText) {

        Alert alert = new Alert(alertType);
        alert.setTitle(windowTitle);
        alert.setHeaderText(titleText);

        // making contentText Optional
        if(contentText != null) {
            alert.setContentText(contentText);
        }

        alert.show();
    }
}
