import pandas as pd
import numpy as np
from Node import Node

from sklearn.model_selection import train_test_split

class myDecisionTreeREPrune:

    def __init__(self, criterion, prune):
        self.criterion = criterion # Guarda o valor de criterion
        self.prune = prune # Guarda o valor do prune

    def fit(self, x_train, y_train):

        global dtf

        dtf = pd.DataFrame(data = x_train[0:, 0:], index=[i for i in range(x_train.shape[0])], columns=h1[0,0:])

        dtf.insert(len(dtf.columns), "class", y_train, True)

        print(dtf)

        global tree
        global target_class
        target_class = "class"

        tree = ID3(dtf, dtf, dtf.columns[:-1], target_class="class")

        print("\nPrint Tree")
        print_tree(tree, queue={})

        if (self.prune=="True"):
            # Teria de fazer o prune
            print("\nDevia fazer o prune...")

    def score(self, x_test, y_test):

        data = pd.DataFrame(data=x_test[0:, 0:], index=[i for i in range(x_test.shape[0])], columns=h1[0, 0:])

        data.insert(len(data.columns), "class", y_test, True)

        queries = data.iloc[:, :-1].to_dict(
            orient="records")  # Cria dicionario de queries organizados por [{coluna: valor, ...}], exemplo: [{outlook: sunny, ...}]

        previsoes = pd.DataFrame(columns=[
            "previsoes"])  # Cria uma DataFrame vazia em cuja a coluna chamada previsões guarda as previsões para cada querie

        for i in range(len(data)):  # Calcula a exatidao das previsões
            previsoes.loc[i, "previsoes"] = previs(queries[i], tree)

        resultado = np.sum(previsoes["previsoes"] == data["class"]) / len(data)

        return resultado

def entropy(target_col): # Calcula a Entropia

    elementos, el_ocorrencias = np.unique(target_col, return_counts=True)
    # elementos -> lista de elementos da colunas classe que existem para um determinado atributo
    # el_ocorrencias -> lista com nº de ocorrencias para cada elemento da lista acima

    for i in range(len(elementos)):
        entropy = np.sum([(-el_ocorrencias[i] / np.sum(el_ocorrencias)) * np.log2(el_ocorrencias[i] / np.sum(el_ocorrencias))])

    return entropy

def gini(target_col): # Calcula o Gini

    elementos, el_ocorrencias = np.unique(target_col, return_counts=True)

    if len(elementos) == 1:
        gini = 0
        return gini

    gini = 1

    for i in range(len(elementos)):
        gini = gini * (el_ocorrencias[i] / np.sum(el_ocorrencias))

    return gini

def InfoGain(data, split_attribute_name, target_name):
    """
    Calcula a info_gain para a data. Recebe 3 parametros:
    1. data = É data para cada atributo que o IG deve calcular
    2. split_attribute_name = nome do atributo split
    3. target_name = o nome da coluna da target_classe, decidimos usar como default o nome de "class" para a coluna target.
    """
    total_entropy = entropy(data[target_name]) # Calcula a entropia da database total

    total_gini = gini(data[target_name]) # Calcula o gini da database total

    # Depois do split, calcula para cada atributo existente o numero de ocorrencias
    atr, atr_ocorr = np.unique(data[split_attribute_name], return_counts=True)

    # Calcula o peso da entropia
    Peso_Entropy = np.sum(
        [(atr_ocorr[i] / np.sum(atr_ocorr)) * entropy(data.where(data[split_attribute_name] == atr[i]).dropna()[target_name])
         for i in range(len(atr))])

    # Calcula o peso do gini
    Peso_Gini = np.sum(
        [(atr_ocorr[i] / np.sum(atr_ocorr)) * 2 * gini(
            data.where(data[split_attribute_name] == atr[i]).dropna()[target_name])
         for i in range(len(atr))])

    # Calcula a Info_Gain depedendo do paramentro do classifier ("entropy" ou "gini")
    if (classifier.criterion == "entropy"):

        Information_Gain = total_entropy - Peso_Entropy

    elif (classifier.criterion == "gini"):

        Information_Gain = total_gini - Peso_Gini

    return Information_Gain

def ID3(data, original_data, features, target_class):
    """
    ID3 Algorithm: Esta função tem 4 argumentos:
    1. data = data que vai sendo alterada dependendo do atributo escolhido
    2. original_data = É a data original que se mantem sempre inalterada
    3. features = conjunto de atributos do data
    4. target_class = o nome da classe target, definida por nos como default = "class"
    """

    root = Node(None)

    if len(np.unique(data[target_class])) <= 1: # Se todos os valores do atributo forem iguais retorna esse mesmo valor
        return np.unique(data[target_class])[0]

    elif len(data) == 0: # Se a data estiver vazia retorna o valor maior/mais provavel presente na original_data
        return np.unique(original_data[target_class])[
            np.argmax(np.unique(original_data[target_class], return_counts=True)[1])]

    elif len(features) == 0:
        root = Node(None)
        return root

    else:

        # Seleciona o atributo que melhor divide a data
        item_values = [InfoGain(data, feature, target_class) for feature in
                       features]  # Retorna a info_gain para cada atributo

        best_feature_index = np.argmax(item_values) # Guarda o indice do melhor atributo

        best_feature = features[best_feature_index] # Guarda o melhor atributo

        root.label = best_feature # Inicializa a arvore. A raiz/root vai ser o nome do atributo classificado como (best_feature)

        features = [i for i in features if i != best_feature] # Remove o atributo com melhor info_gain da lista de atributos

        for value in np.unique(data[best_feature]):

            value = value

            sub_data = data.where(data[best_feature] == value).dropna() # Faz split da data ao longo dos valores dos atributos com mais info_gain e cria as sub_data

            subtree = ID3(sub_data, data, features, target_class) # Chama o algortimo ID3 recursivamente para cada sub_data com os novos parametros

            root.children[value] = subtree # Adiciona a subtree

        return root

def maxprob(original_data, target_class):
    return np.unique(original_data[target_class])[
        np.argmax(np.unique(original_data[target_class], return_counts=True)[1])]

def previs(query, tree):

    for key in list(query.keys()):

        if key == tree.label:
            temp = query[key]
            if temp in list(tree.children.keys()):

                try:
                    result = tree.children.get(temp)

                except:
                    return maxprob(dtf, target_class)

                result = tree.children.get(temp)

                if isinstance(result, dict):
                    return previs(query, result)

                elif isinstance(result, Node):
                    return previs(query, result)

                else:
                    return result

def print_tree(tree, queue):

    if tree.label != None:
        print(tree.label)

    queue.update(tree.children)
    print(tree.children)
    kkeys = list(queue.keys())

    for x in range(len(kkeys)):

        if type(queue[kkeys[x]]) is not Node:
            del queue[kkeys[x]]

        elif type(queue[kkeys[x]]) is Node:
            tree = queue[kkeys[x]]
            del queue[kkeys[x]]
            return print_tree(tree, queue)

if __name__ == '__main__':

    data = np.genfromtxt("weather.nominal.csv", delimiter=",", dtype=None, encoding=None)

    global h1
    h1 = data[0:1, 0:-1]

    xdata = data[1:, 0:-1]  # dados: da segunda à ultima linha, da primeira à penúltima coluna

    ydata = data[1:, -1]  # classe: da segunda à ultima linha, só última coluna

    x_train, x_test, y_train, y_test = train_test_split(xdata, ydata, random_state=0)

    classifier = myDecisionTreeREPrune(criterion="entropy", prune="False")

    classifier.fit(x_train, y_train)

    result = classifier.score(x_test, y_test)

    print("\nPercentagem de casos corretamente classificados {:2.2%}".format(result))
