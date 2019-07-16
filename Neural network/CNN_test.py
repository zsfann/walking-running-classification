#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Project : Advanced Operating System Project

Caracteristics : Creation of Neuronal Network
Creation date : 11/05/2019
Authors : David  BRELLMANN & Shufan ZHANG

Content :
    create_model: function
    LossHistory: object
    main: function

"""

import numpy as np
import pandas as pd


from keras.models import Sequential
from keras.layers import Dense
from keras.wrappers.scikit_learn import KerasClassifier
from keras.callbacks import Callback
from keras.callbacks import EarlyStopping
from keras.utils.np_utils import to_categorical

from sklearn.model_selection import learning_curve, GridSearchCV, KFold, cross_val_score, train_test_split

def create_model(): 
    """
            Create a keras model (the Neuronal Network)
            
            Return
            ----------
            model: Sequential
                data wanted          
        """
    
    global model
    global nb_neurones ## number of neurones per layer
    global nb_layers ## nb_layers-1 is the number of layers in the NN
    model = Sequential()
    
    ## Definition of the layers 
    
    model.add(Dense(nb_neurones, input_dim=200, activation='softmax')) ## input layer
    for l in range(nb_layers):
        model.add(Dense(nb_neurones, activation='softmax'))
    model.add(Dense(2, activation='softmax')) ## output layer

    # Creation of the model
    
    model.compile(loss='categorical_crossentropy', optimizer='adam', metrics=['accuracy'])
    
    return model

class LossHistory(Callback):
    """
        Class containing the logs for the training
    """
    def on_train_begin(self, logs={}):
        self.losses = []

    def on_batch_end(self, batch, logs={}):
        self.losses.append(logs.get('loss'))
        
if __name__  == '__main__':  ## main 
    
    db = pd.read_csv('gyro_y.csv') ## get the database
    dataset = db.values
    X = dataset[:,1:201].astype(float) ## sensor data
    Y = dataset[:,201].astype(int) ## labels
    
    begin=5 ## number of the neurones at the beginning  5
    end=45 ## number of neurones studied at the end     45
    
    for j in range(1,3): ## j = number of hidden layers
    
        rate_neurones=np.zeros((end-begin+1,3), dtype=float)
        nb_layers=j
        
        for i in range(begin,end+1): ## i = number of neurones per layer
            print(j,i)
            loss_history = LossHistory()
            early_stopping = EarlyStopping(monitor='val_acc', patience=20)
            
            nb_neurones=i
            estimator = KerasClassifier(create_model, epochs=200, batch_size=100, verbose=0)
            
            X_train, X_test, Y_train, Y_test = train_test_split(X, Y, test_size=0.33, random_state=5)
            Y_test = to_categorical(Y_test, num_classes=2)
            
            results = estimator.fit(X_train, Y_train, callbacks=[loss_history, early_stopping], validation_data=(X_test, Y_test))
            
            kfold = KFold(n_splits=10, shuffle=True, random_state=5)
            cv_results = cross_val_score(estimator, X_test, Y_test, cv=kfold)
            print("Baseline on test data: %.2f%% (%.2f%%)" % (cv_results.mean()*100, cv_results.std()*100))
            
            rate_neurones[i-begin][0]=i
            rate_neurones[i-begin][1]=cv_results.mean()*100
            rate_neurones[i-begin][2]=cv_results.std()*100
            
        print(rate_neurones)
        
        results=pd.DataFrame(rate_neurones, columns=list(np.arange(3)))
        results.to_csv('res'+str(j)+'.csv')





























