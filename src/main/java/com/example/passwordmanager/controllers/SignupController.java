package com.example.passwordmanager.controllers;

import com.example.passwordmanager.PasswordManagerApplication;
import com.example.passwordmanager.mongodb.MongoClientConnection;
import com.example.passwordmanager.utility.FormValidator;
import com.example.passwordmanager.utility.ValidationError;
import javafx.fxml.FXML;
import javafx.scene.control.PasswordField;
import javafx.scene.control.TextField;
import javafx.scene.text.Text;


public class SignupController {
    @FXML
    private TextField nameField;

    @FXML
    private TextField emailField;

    @FXML
    private PasswordField passwordField;

    @FXML
    private PasswordField confirmPasswordField;

    @FXML
    private Text nameErrorText;

    @FXML
    private Text emailErrorText;

    @FXML
    private Text passwordErrorText;

    @FXML
    private Text confirmPasswordErrorText;

    @FXML
    private void handleSignUp() {
        String email = emailField.getText();
        String password = passwordField.getText();
        String confirmPassword = confirmPasswordField.getText();
        String fullName = nameField.getText();

        boolean isValid = validate(fullName, email, password, confirmPassword);

        // handle authentication
        if(isValid) {
            System.out.println("Logging you in!");
            boolean isCreated = MongoClientConnection.createUser(fullName, email, password);
            if(isCreated) {
                System.out.println("Account created!");
            }
        }

    }

    private boolean validate(String fullName, String email, String password, String confirmPassword) {
        boolean isValid = true;
        // check if name is empty (>3 make it reusable)
        if(!FormValidator.validateField(fullName)) {
            nameErrorText.setText(ValidationError.INVALID_NAME.getMessage());
            isValid = false;
        }

        // validate email (make it reusable)
        if(!FormValidator.isValidEmail(email)) {
            emailErrorText.setText(ValidationError.INVALID_EMAIL.getMessage());
            isValid = false;
        }

        // validate password (minimum password length is 6)
        if(!FormValidator.isValidPassword(password)) {
           passwordErrorText.setText(ValidationError.SHORT_PASSWORD.getMessage());
           isValid = false;
        }

        // check if password matches with confirm password
        if(!password.equals(confirmPassword)) {
            confirmPasswordErrorText.setText(ValidationError.CONFIRM_INVALID_PASSWORD.getMessage());
            isValid = false;
        }

        // return true if all check pass, return false if one check fails
        return isValid;
    }

    @FXML
    private void removeNameErrorText() {
        nameErrorText.setText("");
    }

    @FXML
    private void removeEmailErrorText() {
        emailErrorText.setText("");
    }

    @FXML
    private void removePasswordErrorText() {
        passwordErrorText.setText("");
    }

    @FXML
    private void removeConfirmPasswordErrorText() {
        confirmPasswordErrorText.setText("");
    }


    @FXML
    private void switchToLogin() {
        try {
            PasswordManagerApplication.switchScene("login.fxml");
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
