g++-10 -std=c++2a main.cpp Model.cpp Layer.cpp Activations.cpp Loss.cpp 2> error.log

if [ -s error.log ];then
    if grep -q "error:" error.log;then
        echo コンパイルエラーが発生しました
    else
        echo "ビルド終了(Warning)"
        ./a.out < in.txt
    fi
else
    echo "ビルド終了(正常)"
    ./a.out < in.txt
fi
echo
