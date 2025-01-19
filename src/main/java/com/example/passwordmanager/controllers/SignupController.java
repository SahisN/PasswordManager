package com.example.passwordmanager.controllers;

import com.example.passwordmanager.PasswordManagerApplication;
import javafx.fxml.FXML;
import javafx.scene.control.PasswordField;
import javafx.scene.control.TextField;

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
    private void handleSignUp() {
        String email = emailField.getText();
        String password = passwordField.getText();
        String confirmPassword = confirmPasswordField.getText();
        String fullName = nameField.getText();

        System.out.println("Full Name: " + fullName);
        System.out.println("Email: " + email);
        System.out.println("Password: " + password);
        System.out.println("Confirm Password: " + confirmPassword);
    }

    private void validate(String fullName, String email, String password, String confirmPassword) {
        // check if name is empty (>3 make it reusable)

        // validate email (make it reusable)

        // validate password (minimum password length is 6)

        // check if password matches with confirm password

        // return true if all check pass, return false if one check fails
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
