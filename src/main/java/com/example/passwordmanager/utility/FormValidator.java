package com.example.passwordmanager.utility;

import java.util.regex.Pattern;

public class FormValidator {
    private static final String EMAIL_REGEX = "^[\\w._%+-]+@[\\w.-]+\\.[a-zA-Z]{2,}$";
    private static final Pattern EMAIL = Pattern.compile(EMAIL_REGEX);
    private static final int MINIMUM_PASSWORD_LENGTH = 6;

    public static Boolean validateField(String fieldString) {
        return !fieldString.trim().isEmpty();
    }

    public static Boolean isValidEmail(String email) {
        return validateField(email) && Pattern.matches(EMAIL_REGEX, email);
    }

    public static Boolean isValidPassword(String password) {
        return validateField(password) && password.length() >= 6;
    }



}
