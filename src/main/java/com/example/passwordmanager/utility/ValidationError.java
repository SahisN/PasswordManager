package com.example.passwordmanager.utility;

public enum ValidationError {
    INVALID_EMAIL("Invalid email format"),
    EMPTY_FIELD("This field cannot be empty"),
    INVALID_NAME("Name Required"),
    SHORT_PASSWORD("Password must be 8 characters long"),
    CONFIRM_INVALID_PASSWORD("Confirm Password does not match Password");

    private final String message;

    ValidationError(String message) {
        this.message = message;
    }

    public String getMessage() {
        return message;
    }
}
