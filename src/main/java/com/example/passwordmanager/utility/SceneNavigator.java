package com.example.passwordmanager.utility;

import com.example.passwordmanager.PasswordManagerApplication;

public class SceneNavigator {
    public static void switchScene(String fxmlFile) {
        try {
            PasswordManagerApplication.switchScene(fxmlFile);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}


