package com.example.passwordmanager.controllers;


import com.example.passwordmanager.PasswordManagerApplication;
import com.example.passwordmanager.utility.FormValidator;
import com.example.passwordmanager.mongodb.MongoClientConnection;
import com.example.passwordmanager.utility.ValidationError;
import javafx.concurrent.Task;
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

    @FXML
    private void handleLogin() {
        // Get values from the fields
        String email = emailField.getText();
        String password = passwordField.getText();

        // Print the values (replace with actual login logic if needed)
        System.out.println("Email: " + email);
        System.out.println("Password: " + password);

        boolean isValid = validateLoginForm(email, password);

        if(isValid) {
            // show progress bar while connecting to database & disable text field
            boolean isLoggedIn = authenticateUser(email,password);

            if(isLoggedIn) {
                System.out.println("Loggin succesfull!!!");
            }

            else {
                System.out.println("login failed");
            }



        }


    }

    private boolean authenticateUser(String email, String password) {
        Task<Boolean> authenticateTask = new Task<Boolean>() {
            @Override
            protected  Boolean call() {
                try {
                    return MongoClientConnection.authenticateUser(email, password);
                }

                catch(Exception e) {
                    System.out.println("Failed");
                    return false;
                }
            }
        };

        authenticateTask.setOnRunning(event -> {
            progressIndicator.setVisible(true);
            disableField(true);
        });

        authenticateTask.setOnSucceeded(event -> {
            progressIndicator.setVisible(false);
            disableField(false);
        });

        // Start the task on new thread
        new Thread(authenticateTask).start();

        return false;
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

    private void disableField(boolean isDisable) {
       emailField.setDisable(isDisable);
       passwordField.setDisable(isDisable);
       loginButton.setDisable(isDisable);
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
