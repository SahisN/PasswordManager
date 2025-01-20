package com.example.passwordmanager;


import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.stage.Stage;

import java.io.IOException;

public class PasswordManagerApplication extends Application {
    private static Stage primaryStage;

    @Override
    public void start(Stage stage) throws IOException {
        primaryStage = stage;
        FXMLLoader fxmlLoader = new FXMLLoader(PasswordManagerApplication.class.getResource("login.fxml"));
        Scene scene = new Scene(fxmlLoader.load());
        stage.setTitle("Password Manager");
        stage.setResizable(false);
        stage.setScene(scene);
        stage.show();
    }

    public static void switchScene(String fxmlFile) throws Exception {
        FXMLLoader loader = new FXMLLoader(PasswordManagerApplication.class.getResource(fxmlFile));
        Scene newScene = new Scene(loader.load());
        primaryStage.setScene(newScene);
    }

    public static void main(String[] args) {
        launch();
    }
}