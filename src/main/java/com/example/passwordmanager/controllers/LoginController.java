package com.example.passwordmanager.controllers;


import com.example.passwordmanager.utility.FormValidator;
import com.example.passwordmanager.utility.RunInBackground;
import com.example.passwordmanager.utility.SceneNavigator;
import com.example.passwordmanager.utility.ValidationError;
import javafx.fxml.FXML;
import javafx.scene.control.Button;
import javafx.scene.control.PasswordField;
import javafx.scene.control.ProgressIndicator;
import javafx.scene.control.TextField;
import javafx.scene.text.Text;


public class LoginController {
    @FXML
    private TextField emailField;

    @FXML
    private PasswordField passwordField;

    @FXML
    private Button loginButton;

    @FXML
    private Text emailTextError;

    @FXML
    private Text passwordTextError;

    @FXML
    private ProgressIndicator progressIndicator;

    private void disableField(boolean isDisable) {
        emailField.setDisable(isDisable);
        passwordField.setDisable(isDisable);
        loginButton.setDisable(isDisable);
    }

    @FXML
    private void handleLogin() {
        // Get values from the fields
        String email = emailField.getText();
        String password = passwordField.getText();

        boolean isValid = validateLoginForm(email, password);

        if(isValid) {
            // show progress bar while connecting to database & disable text field
            RunInBackground.runLoginOrSignUp(email, password, progressIndicator, this::disableField, isLoggedIn -> {
                if(isLoggedIn) {
                    System.out.println("Login Successful");
                }

                else {
                    System.out.println("Login Failed");
                }
            });
        }
    }


    private boolean validateLoginForm(String email, String password) {
        boolean isValid = true;

        if(!FormValidator.isValidEmail(email)) {
            setEmailTextError();
            isValid = false;
        }

        if(!FormValidator.isValidPassword(password)) {
            setPasswordTextError();
            isValid = false;
        }

        return isValid;
    }

    private void setEmailTextError() {
        emailTextError.setText(ValidationError.INVALID_EMAIL.getMessage());
    }

    private void setPasswordTextError() {
        passwordTextError.setText(ValidationError.SHORT_PASSWORD.getMessage());
    }

    @FXML
    private void clearEmailErrorText() {
        emailTextError.setText("");
    }

    @FXML
    private void clearPasswordErrorText() {
        passwordTextError.setText("");
    }


    @FXML
    private void  switchToCreateAccount() {
        SceneNavigator.switchScene("signup.fxml");
    }

}
