#Dependencies
import numpy as np
import pandas as pd
from sklearn.preprocessing import OneHotEncoder
# importing "array" for array creations
import array as arr

#dataset import
dataset = pd.read_csv('Dataset_200.csv') #You need to change #directory accordingly

# creating an array with integer type (np_max)
c = arr.array('i', [0,0,0,0])

#Normalizing the data
from sklearn.preprocessing import StandardScaler
sc = StandardScaler()
temp = sc.fit_transform(dataset.iloc[:, :12].values)
dataset.at[:, :12] = temp


# Shuffle
dataset.sample(frac=1).reset_index(drop=True)


num_rows = dataset.shape[0]
frac = 0.9
X_train = dataset.iloc[:round(num_rows*frac), :12].values
Y_train = dataset.iloc[:round(num_rows*frac), 262:263].values
X_test = dataset.iloc[round(num_rows*frac):, :12].values
Y_test = dataset.iloc[round(num_rows*frac):, 262:263].values

# One Hotting Y
ohe = OneHotEncoder()

Y_train = ohe.fit_transform(Y_train).toarray()
Y_test2 = Y_test
Y_test = ohe.fit_transform(Y_test).toarray()

for i in range(len(Y_test2)):
    if (Y_test2[i] == [15]):
        c[np.argmax(Y_test[i])] = 27
    if (Y_test2[i] == [49]):
        c[np.argmax(Y_test[i])] = 61
    if (Y_test2[i] == [215]):
        c[np.argmax(Y_test[i])] = 227
    if (Y_test2[i] == [1]):
        c[np.argmax(Y_test[i])] = 13
    if (Y_test2[i] == [65]):
        c[np.argmax(Y_test[i])] = 77


#Dependencies
import keras
from keras.models import Sequential
from keras.layers import Dense
# Neural network
model = Sequential()
model.add(Dense(36, input_dim=12, activation="relu"))
model.add(Dense(18, activation="relu"))
model.add(Dense(12, activation="relu"))
model.add(Dense(4, activation="softmax"))
model.compile(loss='categorical_crossentropy', optimizer='adam', metrics=['accuracy'])


history = model.fit(X_train, Y_train, epochs=200, batch_size=4000)
score, acc = model.evaluate(x=X_test, y=Y_test)
print('Test Accuracy: ' + str(acc))


y_pred = model.predict(X_test)
pred = list()
Y_predValue = 0
counter_pred = 0

for i in range(len(y_pred)):
    pred.append(np.argmax(y_pred[i]))
    counter_pred = counter_pred + 1
    Y_predValue = Y_predValue + dataset.iloc[round(num_rows * frac) + i : round(num_rows * frac) + i+1, c[np.argmax(y_pred[i])]-1].values

test = list()
Y_testValue = 0
Y_MABValue = 0
counter = 0

for i in range(len(Y_test)):
    test.append(np.argmax(Y_test[i]))
    counter = counter + 1
    Y_testValue = Y_testValue + dataset.iloc[round(num_rows * frac) + i : round(num_rows * frac) + i+1, c[np.argmax(Y_test[i])]-1].values
    Y_MABValue = Y_MABValue + dataset.iloc[round(num_rows * frac) + i : round(num_rows * frac) + i+1, 263].values

print('learning')
print(counter_pred)
print(Y_predValue)
print('optimal')
print(counter)
print(Y_testValue)
print('MAB')
print(Y_MABValue)

from sklearn.metrics import accuracy_score
a = accuracy_score(pred,test)
print('Accuracy is:', a*100)


