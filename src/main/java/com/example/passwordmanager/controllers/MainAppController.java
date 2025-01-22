package com.example.passwordmanager.controllers;

import de.jensd.fx.glyphs.fontawesome.FontAwesomeIconView;
import javafx.fxml.FXML;
import javafx.scene.layout.Pane;
import javafx.scene.paint.Paint;

public class MainAppController {
    private final Paint ACTIVE_COLOR = javafx.scene.paint.Paint.valueOf("#2e78f8");
    private final Paint INACTIVE_COLOR = javafx.scene.paint.Paint.valueOf("#c9bebe");

    @FXML
    private FontAwesomeIconView homeIcon;

    @FXML
    private FontAwesomeIconView settingsIcon;

    @FXML
    private Pane homePage;

    @FXML
    private Pane settingsPage;

    private void setPage(int pageIndex) {
        homePage.setVisible(pageIndex == 0);
        settingsPage.setVisible(pageIndex == 1);
    }

    @FXML
    private void onHomeIconPress() {
        homeIcon.setFill(ACTIVE_COLOR);
        settingsIcon.setFill(INACTIVE_COLOR);
        setPage(0);
    }

    @FXML
    private void onSettingsIconPress() {
        homeIcon.setFill(INACTIVE_COLOR);
        settingsIcon.setFill(ACTIVE_COLOR);
        setPage(1);
    }


}
