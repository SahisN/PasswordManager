package com.example.passwordmanager.mongodb;

import com.example.passwordmanager.utility.UrlEncoder;
import com.mongodb.client.MongoClient;
import com.mongodb.client.MongoClients;
import com.mongodb.client.MongoCollection;
import com.mongodb.client.MongoDatabase;
import org.bson.Document;

public class MongoDBConnector {

    private static final UrlEncoder urlEncoder =  new UrlEncoder("", "");
    private static final String DB_NAME = "userData";
    private static final String COLLECTION_NAME = "user";
    private final MongoCollection<Document> collection;
    private final MongoClient mongoClient;


    public MongoDBConnector() {
        String uri =  urlEncoder.getUri();
        mongoClient = MongoClients.create(uri);
        MongoDatabase database = mongoClient.getDatabase(DB_NAME);

        this.collection = database.getCollection(COLLECTION_NAME);
    }


    public MongoCollection<Document> getCollection() {
        return collection;
    }

    public static String getURL() {
        System.out.println(urlEncoder.getUri());
        return urlEncoder.getUri();
    }

    public void close() {
        mongoClient.close();
    }
}
