# minishell

### 檔案
最終提交檔案
1. Makefile
2. srcs/*
3. includes/*
開發用
1. todo.txt
2. tester/*

### 工作分配
1. libft (make a tester and check norm)
2. Makefile
3. main.c, minishell.h (這兩個檔案以整合parse, execute為目標，並且只將共用prototype放入minishell.h)
4. parse (xli)
5. execute (yfu)

### 注意事項
1. 每次進行修改時另開branch，等到所有人+tester都驗證完功能以後再進行merge，詳見參考資料1
2. 每個功能都盡可能多次commit，並清楚撰寫commit message（中或英文)， 詳見參考資料2
3. 檔案名稱與函式名稱務必以易理解為原則
4. 寫註解，讓所有人都能看懂為佳，至少要確保以後的自己仍看得懂並能清楚解釋
5. norm是最後一步，確定功能完備前不宜為norm而破壞可讀性

### 參考資料
1. git branch

https://git-scm.com/book/zh/v2/Git-%E5%88%86%E6%94%AF-%E5%88%86%E6%94%AF%E7%9A%84%E6%96%B0%E5%BB%BA%E4%B8%8E%E5%90%88%E5%B9%B6

2. git commit message

https://chris.beams.io/posts/git-commit/
