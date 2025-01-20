package com.example.passwordmanager.utility;

import com.mongodb.client.MongoClient;
import com.mongodb.client.MongoClients;

import java.net.URLEncoder;

public class UrlEncoder {

    private String username;
    private String password;


    public UrlEncoder(String username, String password) {
        this.username = username;
        this.password = password;
    }


    public String getUri() {
        try {
            String username = URLEncoder.encode(this.username, "UTF-8");
            String password = URLEncoder.encode(this.password, "UTF-8");


            String uri = "mongodb+srv://" + username + ":" + password +
                    "@cluster0.wrya6.mongodb.net/?retryWrites=true&w=majority&appName=Cluster0";


            return uri;
        }

        catch(Exception e) {
            System.err.println(e.getCause());
        }

        return null;
    }


}
