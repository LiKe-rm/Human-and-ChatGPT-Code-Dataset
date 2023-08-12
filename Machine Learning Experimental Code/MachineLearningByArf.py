import pandas as pd
import numpy as np
import os
from sklearn.model_selection import train_test_split, KFold, cross_val_score
from sklearn.pipeline import make_pipeline
from sklearn.preprocessing import StandardScaler
from sklearn.ensemble import RandomForestClassifier
from sklearn.metrics import classification_report, confusion_matrix, accuracy_score


def get_name_field_type(line):
    if line.find("'") == 11:
        temp = line.split("'")
        attr = temp[0][:-1]
        name = temp[1]
        field_type = temp[2][1:]
    else:
        try:
            attr,name,field_type = line.split()
        except:
            print(line)
    return attr,name,field_type


def read_sparse_arrf(file):
    with open(file, encoding="utf-8") as f:
        header = []
        default_field = {}
        field_num = 0
        for line in f:
            if line.startswith("@attribute") or line.startswith("@ATTRIBUTE"):
                _, name, field_type = get_name_field_type(line)
                header.append(name)
                if field_type.startswith("{"):
                    default_field[field_num] = field_type[1:-1].split(",")[0]
                field_num += 1
            elif line.startswith("@data") or line.startswith("@DATA"):
                break
        default_field_keys = set(default_field.keys())
        width = len(header)
        data = []
        for line in f:
            line = line.strip()
            if not line:
                continue
            tmp = [0]*width
            flags = set()
            for kv in line[1:-1].split(","):
                if kv == '':
                    break
                k, v = kv.split()
                k = int(k)
                flags.add(k)
                tmp[k] = v
            for k in default_field_keys-flags:      # 将稀疏矩阵每行中未出现的，字典类型的属性，置为默认值（即第一个值）
                tmp[k] = default_field[k]
            data.append(tmp)
    # return pd.DataFrame(data, columns=header)
    return data,header



def train_rfc(dataset, label):
    kf = KFold(n_splits=10, shuffle=True)
    lt = []
    lt = label
    dataset = np.array(dataset, dtype = 'float32')
    lt = np.array(lt, dtype = 'float32')
    count = 0
    for train_index,test_index in kf.split(dataset, lt):
                # train_index 就是分类的训练集的下标，test_index 就是分配的验证集的下标
        this_train_x, this_train_y = dataset[train_index,:], lt[train_index]  # 本组训练集
        this_test_x, this_test_y = dataset[test_index,:], lt[test_index]  # 本组验证集
        rf = RandomForestClassifier(n_estimators=90)
        #rf = KNeighborsClassifier()
        #rf = IsolationForest()
        #rf = LogisticRegression()
        #rf = SVC()
        rf.fit(this_train_x, this_train_y)
        y_preds = rf.predict(this_test_x)
        count += 1
        print(f"\nThe {count} fold.")
        print("Confusion Matrix:\n", confusion_matrix(this_test_y, y_preds))
        print("Classification Report:\n", classification_report(this_test_y, y_preds))
        print("Accuracy:", accuracy_score(this_test_y, y_preds))


def rfk(X_train, y_train):
    X_train = np.array(X_train, dtype = 'float32')
    y_train = np.array(y_train, dtype = 'int64')
    pipeline = make_pipeline(StandardScaler(), RandomForestClassifier(n_estimators=90))
    strtfdKFold = KFold(n_splits=10, shuffle=True)
    kfold = strtfdKFold.split(X_train, y_train)
    #循环迭代，（K-1）份用于训练，1份用于验证，把每次模型的性能记录下来。
    scores = []
    for k, (train, test) in enumerate(kfold):
        pipeline.fit(X_train[train,:], y_train[train])
        score = pipeline.score(X_train[test,:], y_train[test])
        scores.append(score)
        print('Fold: %2d, Training/Test Split Distribution: %s, Accuracy: %.3f' % (k+1, np.bincount(y_train[train]), score))
    print('\n\nCross-Validation accuracy: %.3f +/- %.3f' %(np.mean(scores), np.std(scores)))
                    


def main():
    data,header = read_sparse_arrf("/home/codedataset/ExternalStorage/authorship/dataset/4v2test.arff")
    cons=[]
    label=[]
    for new_da in data:
        if "NaN" in new_da:
            continue
        
        if new_da[1] == 'male':
            new_da[1] = 1
        elif new_da[1] == 'female':
            new_da[1] = 0
        
        if new_da[11319] == 'true':
            new_da[11319] = 1
        else:
            new_da[11319] = 0
        if new_da[11320] == 'true':
            new_da[11320] = 1
        else:
            new_da[11320] = 0
        
        if new_da[13653] == 'true':
            new_da[13653] = 1
        else:
            new_da[13653] = 0
        if new_da[13654] == 'true':
            new_da[13654] = 1
        else:
            new_da[13654] = 0
            
        label.append(new_da[0])      # 性别预测，就选new_da[1]， 作者预测就选new_da[0]
        cons.append(new_da[2:])
    # train_rfc(cons, author_label)
    rfk(cons, label)


def test():
    X_train = np.array([0,1,2,3,4,5,6,7,8,9,10,11])
    Y_train = np.array([[0,0],[1,1],[2,2],[3,3],
                        [4,4],[5,5],[6,6],[7,7],
                        [8,8],[9,9],[10,10],[11,11]])
    train_X, test_X, train_y, test_y = train_test_split(X_train, Y_train, 
                                                        test_size = 0.25,           # test_size决定划分的比例
                                                        random_state = 10,          # 只要random_state设置为定值，那么每次划分都是一样的
                                                        shuffle = True)             # shuffle决定是否进行划分
    print(train_X)
    print(test_X)
    # print(train_y)
    # print(test_y)

if __name__ == "__main__":
    main()
    # test()



