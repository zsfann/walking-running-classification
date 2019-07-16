#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Project : Advanced Operating System Project

Caracteristics : Creation of databases usable by the Neuronal Network
Creation date : 10/05/2019
Authors : David  BRELLMANN & Shufan ZHANG

Content :
    create_db_for_nn: function

"""

import warnings
warnings.filterwarnings('ignore')

import numpy as np
import pandas as pd

def create_db_for_nn(attribute, name_file):
    """
            Create a database usable by the Neuronal Network
            
            Parameters
            ----------
            atribute: string
                data wanted
                
            name_file: int
                name of the database generated
            
        """

    db = pd.read_csv('database.csv') ## load the database
    
    attribute_values = db[attribute].values ## get the wanted values
    
    activity = db["activity"].values
    username = db["username"].values
    wrist = db["wrist"].values
    
    WALK=0
    RUN=1
    
    n=len(attribute_values)
    walk_session_change=[] ## list of tuples giving the first and the last index of different saved sessions
    run_session_change=[] ## list of tuples giving the first and the last index of different saved sessions
    first_index=0
    last_index=0
    nb_data=0 ## number of data saved in the new database
    
    ## Compute walk_session_change and run_session_change
    ## 201 measures = 2s  time to make a move when you walk or run
    
    for i in range(1,n):
        if username[i]!=username[i-1] or wrist[i]!=wrist[i-1]: ## when we are in a different saved session
            extend=(i-first_index-1)-(i-first_index-1)%200
            nb_data+=extend
            if activity[i-1]==WALK:
                last_index=first_index+extend
                walk_session_change.append((first_index, last_index))
                first_index=i
            if activity[i-1]==RUN:
                last_index=first_index+extend
                run_session_change.append((first_index, last_index))
                first_index=i
    gap=(n-first_index-1)-(n-first_index-1)%200
    nb_data+=gap
    if activity[n-1]==WALK:
        last_index=first_index+gap
        walk_session_change.append((first_index, last_index))
    else:
        last_index=first_index+gap
        run_session_change.append((first_index, last_index))
        
    ## Creation of the new database
      
    new_attribute_values=np.zeros((nb_data//200, 201),dtype=int) 
    
    count=0
    for i in range(len(walk_session_change)):
        for j in range(walk_session_change[i][0],walk_session_change[i][1]):
            new_attribute_values[count//200][count%200]=attribute_values[j]
            new_attribute_values[count//200][200]=WALK
            count+=1
            
    for i in range(len(run_session_change)):
        for j in range(run_session_change[i][0],run_session_change[i][1]):
            new_attribute_values[count//200][count%200]=attribute_values[j]
            new_attribute_values[count//200][200]=RUN
            count+=1
            
    n_db=pd.DataFrame(new_attribute_values, columns=list(np.arange(201)))
    n_db.to_csv(name_file)
    
if __name__  == '__main__':  ## main 
    create_db_for_nn("acceleration_x", 'acceleration_x.csv')
    create_db_for_nn("acceleration_y", 'acceleration_y.csv')
    create_db_for_nn("acceleration_z", 'acceleration_z.csv')
    create_db_for_nn("gyro_x", 'gyro_x.csv') 
    create_db_for_nn("gyro_y", 'gyro_y.csv') 
    create_db_for_nn("gyro_z", 'gyro_z.csv') 
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    