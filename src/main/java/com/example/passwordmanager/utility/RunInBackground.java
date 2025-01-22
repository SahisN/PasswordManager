package com.example.passwordmanager.utility;

import com.example.passwordmanager.mongodb.MongoClientConnection;
import javafx.concurrent.Task;
import javafx.scene.control.ProgressIndicator;

import java.util.function.Consumer;

public class RunInBackground {
    public static void runLoginOrSignUp(String email, String password, ProgressIndicator progressIndicator, Consumer<Boolean> action, Consumer<Boolean> onComplete) {

        Task<Boolean> authenticateTask = new Task<>() {
            @Override
            protected Boolean call() {
                try {
                    return MongoClientConnection.authenticateUser(email, password);
                } catch (Exception e) {
                    System.out.println("Failed");
                }
                return false;
            }
        };

        authenticateTask.setOnRunning(event -> {
            progressIndicator.setVisible(true);
            action.accept(true);
        });

        authenticateTask.setOnSucceeded(event -> {
            progressIndicator.setVisible(false);
            action.accept(false);
            onComplete.accept(authenticateTask.getValue());
        });

        authenticateTask.setOnFailed(event -> {
            progressIndicator.setVisible(false);
            action.accept(false);
            onComplete.accept(false);
        });


        // Start the task on new thread
        new Thread(authenticateTask).start();

        System.out.println("this fails instantly");
    }
}
