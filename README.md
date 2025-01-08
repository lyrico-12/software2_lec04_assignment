# software2_lec04_assignment
## 課題２　線形単回帰分析

data.csvファイルを`fgets`で一行ずつ読み取り、線形リストの構造体`Sample`に格納。それぞれの回帰係数についてgradientを計算し、最急降下法の最適化により、単回帰分析を実装した。

## 課題３　線形重回帰分析
発展課題として、線形重回帰分析を実装した。

### 分析対象
`adv/src/AdsBud_and_Sales.csv`のデータで、これは説明変数が、TV Ad Budget, Radio Ad Budget, Newspaper Ad Budget、目的変数がSalesである。全てdollar単位。

### 分析の手順
1. 分析データのcsvファイルを一行ずつ読み取って、線形リストの構造体Dataに保管しておく。
2. trainデータとtestデータに分割する。train:test = 8:2に分割し、2次元配列の`dataset`に保管する。これは`dataset[data length][5]`となっていて、第1変数は便宜上全て1.0。第2引数はTV Ad Budget、第３引数はRadio Ad Budget、第4引数はNewspaper Ad Budget、第5引数は目的変数のSalesである。
3. 線形重回帰分析において、各データは標準化する必要があるため、traindataとtestdataをそれぞれ標準化(`standerdization`)。
4. 最急降下法の最適化を用いて、線形重回帰分析を実行(`optimize`)。
5. 分析の結果表示。目的変数の予測値と実測値、またその差の絶対値を表示(`print_result`)。
6. 重回帰分析モデルの評価。最適化時のイテレーションと決定係数をtrain, testそれぞれについて表示。
