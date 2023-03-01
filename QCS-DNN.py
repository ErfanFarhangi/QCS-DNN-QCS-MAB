#Dependencies
import numpy as np
import pandas as pd
from sklearn.preprocessing import OneHotEncoder

#dataset import
dataset = pd.read_csv('Dataset_25.csv') #You need to change #directory accordingly

# importing "array" for array creations
import array as arr

# creating an array with integer type (np_max)
Latency = arr.array('i', [0,0,0,0])

# creating an array with integer type (np_max)
Content_Delivery = arr.array('i', [0,0,0,0])

# creating an array with integer type (np_max)
Handover = arr.array('i', [0,0,0,0])

#Normalizing the data
from sklearn.preprocessing import StandardScaler
sc = StandardScaler()
temp = sc.fit_transform(dataset.iloc[:, :4].values)
dataset.at[:, :4] = temp

# Shuffle
dataset.sample(frac=1).reset_index(drop=True)

num_rows = dataset.shape[0]
frac = 0.8
X_train = dataset.iloc[:round(num_rows*frac), :4].values
Y_train = dataset.iloc[:round(num_rows*frac), 28:29].values
X_test = dataset.iloc[round(num_rows*frac):, :4].values
Y_test = dataset.iloc[round(num_rows*frac):, 28:29].values


# One Hotting Y
ohe = OneHotEncoder()
Y_train = ohe.fit_transform(Y_train).toarray()
Y_test2 = Y_test
Y_test = ohe.fit_transform(Y_test).toarray()

for i in range(len(Y_test2)):
    if (Y_test2[i] == [2]):
        Latency[np.argmax(Y_test[i])] = 6
    if (Y_test2[i] == [4]):
        Latency[np.argmax(Y_test[i])] = 8
    if (Y_test2[i] == [6]):
        Latency[np.argmax(Y_test[i])] = 10
    if (Y_test2[i] == [8]):
        Latency[np.argmax(Y_test[i])] = 12

for i in range(len(Y_test2)):
    if (Y_test2[i] == [2]):
        Content_Delivery[np.argmax(Y_test[i])] = 14
    if (Y_test2[i] == [4]):
        Content_Delivery[np.argmax(Y_test[i])] = 16
    if (Y_test2[i] == [6]):
        Content_Delivery[np.argmax(Y_test[i])] = 18
    if (Y_test2[i] == [8]):
        Content_Delivery[np.argmax(Y_test[i])] = 20

for i in range(len(Y_test2)):
    if (Y_test2[i] == [2]):
        Handover[np.argmax(Y_test[i])] = 22
    if (Y_test2[i] == [4]):
        Handover[np.argmax(Y_test[i])] = 24
    if (Y_test2[i] == [6]):
        Handover[np.argmax(Y_test[i])] = 26
    if (Y_test2[i] == [8]):
        Handover[np.argmax(Y_test[i])] = 28

#Dependencies
import keras
from keras.models import Sequential
from keras.layers import Dense
# Neural network
model = Sequential()

model.add(Dense(36, input_dim=4, activation="relu"))
model.add(Dense(18, activation="relu"))
model.add(Dense(12, activation="relu"))
model.add(Dense(4, activation="softmax"))


model.compile(loss='categorical_crossentropy', optimizer='adam', metrics=['accuracy'])

history = model.fit(X_train, Y_train, epochs=200, batch_size=8000)
score, acc = model.evaluate(x=X_test, y=Y_test)
print('Test Accuracy: ' + str(acc))

y_pred = model.predict(X_test)

pred = list()
Y_predLatency = 0
Y_predContentDelivery = 0
Y_predHandover = 0
counter_pred = 0
counter_handover = 0
past = Latency[np.argmax(y_pred[0])]
for i in range(len(y_pred)):
    pred.append(np.argmax(y_pred[i]))
    counter_pred = counter_pred + 1
    current = Latency[np.argmax(y_pred[i])]
    if (past != current):
        counter_handover = counter_handover + 1
        Y_predHandover = Y_predHandover + dataset.iloc[round(num_rows * frac) + i: round(num_rows * frac) + i + 1,Handover[np.argmax(y_pred[i])] - 1].values
    past = current
    Y_predLatency = Y_predLatency + dataset.iloc[round(num_rows * frac) + i : round(num_rows * frac) + i+1, Latency[np.argmax(y_pred[i])]-1].values
    Y_predContentDelivery = Y_predContentDelivery + dataset.iloc[round(num_rows * frac) + i : round(num_rows * frac) + i+1, Content_Delivery[np.argmax(y_pred[i])]-1].values


test = list()
Y_testLatency = 0
Y_MABLatency = 0
Y_EpsilonGreedyLatency = 0

Y_testContentDelivery = 0
Y_MABContentDelivery = 0
Y_EpsilonGreedyContentDelivery = 0

Y_testHandover = 0
Y_MABHandover = 0
Y_EpsilonGreedyHandover = 0
counter = 0
for i in range(len(Y_test)):

    test.append(np.argmax(Y_test[i]))
    counter = counter + 1

    Y_testLatency = Y_testLatency + dataset.iloc[round(num_rows * frac) + i : round(num_rows * frac) + i+1, Latency[np.argmax(Y_test[i])]-1].values
    Y_MABLatency = Y_MABLatency + dataset.iloc[round(num_rows * frac) + i : round(num_rows * frac) + i+1, 29].values
    Y_EpsilonGreedyLatency = Y_EpsilonGreedyLatency + dataset.iloc[round(num_rows * frac) + i : round(num_rows * frac) + i+1, 32].values

    Y_testContentDelivery = Y_testContentDelivery + dataset.iloc[round(num_rows * frac) + i : round(num_rows * frac) + i+1, Content_Delivery[np.argmax(Y_test[i])]-1].values
    Y_MABContentDelivery = Y_MABContentDelivery + dataset.iloc[round(num_rows * frac) + i : round(num_rows * frac) + i+1, 30].values
    Y_EpsilonGreedyContentDelivery = Y_EpsilonGreedyContentDelivery + dataset.iloc[round(num_rows * frac) + i : round(num_rows * frac) + i+1, 33].values

    Y_testHandover = Y_testHandover + dataset.iloc[round(num_rows * frac) + i : round(num_rows * frac) + i+1, Handover[np.argmax(Y_test[i])]-1].values
    Y_MABHandover = Y_MABHandover + dataset.iloc[round(num_rows * frac) + i : round(num_rows * frac) + i+1, 31].values
    Y_EpsilonGreedyHandover = Y_EpsilonGreedyHandover + dataset.iloc[round(num_rows * frac) + i : round(num_rows * frac) + i+1, 34].values



print('DNN')
print(counter_pred)
print(counter_handover)
print(Y_predLatency)
print('optimal')
print(counter)
print(Y_testLatency)
print('MAB')
print(Y_MABLatency)
print('Epsilon Greedy')
print(Y_EpsilonGreedyLatency)

print('DNN')
print(Y_predContentDelivery)
print('optimal')
print(Y_testContentDelivery)
print('MAB')
print(Y_MABContentDelivery)
print('Epsilon Greedy')
print(Y_EpsilonGreedyContentDelivery)

print('DNN')
print(Y_predHandover)
print('optimal')
print(Y_testHandover)
print('MAB')
print(Y_MABHandover)
print('Epsilon Greedy')
print(Y_EpsilonGreedyHandover)

from sklearn.metrics import accuracy_score
a = accuracy_score(pred,test)
print('Accuracy is:', a*100)

