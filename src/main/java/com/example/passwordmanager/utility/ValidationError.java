package com.example.passwordmanager.utility;

public enum ValidationError {
    INVALID_EMAIL("Invalid email format"),
    EMPTY_FIELD("This field cannot be empty"),
    SHORT_PASSWORD("Password must be 8 characters long");

    private final String message;

    ValidationError(String message) {
        this.message = message;
    }

    public String getMessage() {
        return message;
    }
}
