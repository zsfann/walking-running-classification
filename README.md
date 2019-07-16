# walking-running-classification
Advanced Operation System course project

In the folder [Neural network] you can find the database for training and testing of our neural network and 3 scripts. "database_treatment.py" is used to arrange data for training and testing. "CNN_test.py" performs a series of tests to find parameters of neural network in order to achieve good prediction accuracy. "CNN.py" creates the neural network model.

The folder [miosix-receiving-data] contains the program and drivers allowing to receive measurement results from the sensor. It also contains the AI library generated from our neural network but it's not used.

The folder [miosix-with-ai] contains "main.cpp" and "Makefile" to replace the files of the same names in [miosix-receiving-data] in order to implement the neural network by using the AI library. However they don't work.
