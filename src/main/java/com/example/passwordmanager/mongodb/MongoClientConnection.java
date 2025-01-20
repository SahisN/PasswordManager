package com.example.passwordmanager.mongodb;

import com.example.passwordmanager.dialogs.AlertDialog;
import com.mongodb.*;
import com.mongodb.client.MongoClient;
import com.mongodb.client.MongoClients;
import com.mongodb.client.MongoCollection;
import com.mongodb.client.MongoDatabase;
import com.mongodb.client.result.InsertOneResult;
import javafx.scene.control.Alert;
import org.bson.Document;
import org.mindrot.jbcrypt.BCrypt;

public class MongoClientConnection {
    public static void checkConnection() {
        String URL = MongoDBConnector.getURL();

        ServerApi serverApi = ServerApi.builder()
                .version(ServerApiVersion.V1)
                .build();

        MongoClientSettings settings = MongoClientSettings.builder()
                .applyConnectionString(new ConnectionString(URL))
                .serverApi(serverApi)
                .build();

        // Create a new client and connect to the server
        try(MongoClient mongoClient = MongoClients.create(settings)) {
            try {
                // Send a ping to confirm a successful connection
                MongoDatabase database = mongoClient.getDatabase("admin");
                database.runCommand(new Document("ping", 1));
                System.out.println("Pinged your development. You have successfully connected to MongoDB!");
            }

            catch(MongoException e){
                e.printStackTrace();
            }

        }
    }

    public static String hashPassword(String password) {
        return BCrypt.hashpw(password, BCrypt.gensalt());
    }

    public static boolean createUser(String fullName, String email, String password) {
        MongoDBConnector dbConnector = new MongoDBConnector();
        MongoCollection<Document> collection = dbConnector.getCollection();

        // check if email exist
        Document existingUser = collection.find(new Document("email", email)).first();
        if(existingUser != null) {
            System.out.println(existingUser);
            AlertDialog.showPopUp(Alert.AlertType.INFORMATION,"Unable to create account", "User already exist", "This user already has an account. Please try different email");
            dbConnector.close();
            return false;
        }

        // if email does not exist, then create a new user
        Document user = new Document("Full Name", fullName)
                .append("email", email)
                .append("password", hashPassword(password));

        try {
            InsertOneResult result = collection.insertOne(user);

            if(result.wasAcknowledged()) {
                AlertDialog.showPopUp(Alert.AlertType.INFORMATION, "Account Created", "User account has been created", null);
                return true;
            }

            else {
                AlertDialog.showPopUp(Alert.AlertType.ERROR, "Account Creation Failed", "User account has not been created. Please try again later", null);
            }
        }

        catch(MongoSocketOpenException e) {
            AlertDialog.showPopUp(Alert.AlertType.ERROR, "Connection Error", "Network Error", e.getMessage());
        } catch (Exception e) {
            AlertDialog.showPopUp(Alert.AlertType.ERROR, "Error", "Unexpected Error", null);
        }

        dbConnector.close();
        return false;

    }

    public static boolean authenticateUser(String email, String password) {
        MongoDBConnector dbConnector = new MongoDBConnector();
        MongoCollection<Document> collection = dbConnector.getCollection();

        // check if user does not exist
        Document existingUser = collection.find(new Document("email", email)).first();
        if(existingUser == null) {
            AlertDialog.showPopUp(Alert.AlertType.ERROR, "Login Failed", "Email or password is Incorrect", null);
            dbConnector.close();
            return false;
        }

        // if user exist, then authenticate the user
        String userPassword = existingUser.getString("password");
        System.out.println(userPassword);

        // verify password
        if(BCrypt.checkpw(password, userPassword)) {
            System.out.println("Login In!");
            dbConnector.close();
            return true;
        }

        System.out.println("false");
        AlertDialog.showPopUp(Alert.AlertType.ERROR, "Login Failed", "Email or password is Incorrect", null);
        dbConnector.close();
        return false;

    }



}
