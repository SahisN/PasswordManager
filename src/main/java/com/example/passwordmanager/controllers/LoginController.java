package com.example.passwordmanager.controllers;


import com.example.passwordmanager.PasswordManagerApplication;
import javafx.fxml.FXML;
import javafx.scene.control.Button;
import javafx.scene.control.PasswordField;
import javafx.scene.control.TextField;


public class LoginController {
    @FXML
    private TextField emailField;

    @FXML
    private PasswordField passwordField;

    @FXML
    private Button loginButton;


    @FXML
    private void handleLogin() {
        // Get values from the fields
        String email = emailField.getText();
        String password = passwordField.getText();

        // Print the values (replace with actual login logic if needed)
        System.out.println("Email: " + email);
        System.out.println("Password: " + password);
    }

    @FXML
    private void switchToCreateAccount() {
        try {
            PasswordManagerApplication.switchScene("signup.fxml");
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
