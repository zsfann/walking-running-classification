#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import numpy as np
import pandas as pd
from keras.models import Sequential, model_from_json
from keras.layers import Dense
from keras.wrappers.scikit_learn import KerasClassifier
from keras.callbacks import Callback
from keras.callbacks import EarlyStopping
from keras.utils.np_utils import to_categorical

from keras.utils import np_utils
from sklearn import datasets
from sklearn import preprocessing
from sklearn.preprocessing import LabelEncoder

from sklearn.model_selection import learning_curve, GridSearchCV, KFold, cross_val_score, train_test_split

# fix random seed for reproducibility
seed = 7
np.random.seed(seed)

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
    
    model.add(Dense(nb_neurones, input_dim=200, activation='tanh')) ## input layer
    for l in range(nb_layers):
        model.add(Dense(nb_neurones, activation='tanh'))
    model.add(Dense(2, activation='softmax')) ## output layer

    # Creation of the model
    
    model.compile(loss='categorical_crossentropy', optimizer='adam', metrics=['accuracy'])
    
    return model

def save_model(model):
    
    # saving model
    json_model = model.to_json()
    open('model_architecture.json', 'w').write(json_model)
    # saving weights
    model.save_weights('model_weights.h5', overwrite=True)

class LossHistory(Callback):
    """
        Class containing the logs for the training
    """
    def on_train_begin(self, logs={}):
        self.losses = []

    def on_batch_end(self, batch, logs={}):
        self.losses.append(logs.get('loss'))
        
if __name__  == '__main__':  ## main 
    
    db = pd.read_csv('acceleration_x.csv') ## get the database
    dataset = db.values
    X = dataset[:,1:201].astype(float) ## sensor data
    Y = dataset[:,201].astype(int) ## labels
    

    nb_layers=2
    nb_neurones=35
    
    loss_history = LossHistory()
    early_stopping = EarlyStopping(monitor='val_acc', patience=20)
    estimator = create_model()
    
    X_train, X_test, Y_train, Y_test = train_test_split(X, Y, test_size=0.33, random_state=seed)
    Y_test = to_categorical(Y_test, num_classes=2)
    Y_train = to_categorical(Y_train, num_classes=2)
    
    print(X_train.shape)
    
    results =estimator.fit(X_train, Y_train, batch_size=100, epochs=200, callbacks=[loss_history, early_stopping], validation_data=(X_test, Y_test))
    
    # save the model
    #save_model(estimator)
    estimator.save("estimator.h5")


