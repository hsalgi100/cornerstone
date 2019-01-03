
(Grammar
  (Program       (#name (* TopLevel)))
  (TopLevel      (| StrTable Struct Def Decl))
  (StrTable      (str-table (* StrTableEntry)))
  (StrTableEntry (#int String))
  (Struct        (struct Name (* Field)))
  (Field         (#name Type))
  (Def           (def Name Params Type Do))
  (Decl          (decl Name Types Type))
  (Stmt          (| Let Return If Store Auto Do Call))
  (If            (if Expr Stmt))
  (Store         (store Expr Type Expr))
  (Auto          (auto Name Type))
  (Do            (do (* Stmt)))
  (Return        (| ReturnExpr ReturnVoid))
  (ReturnExpr    (return Expr Type))
  (ReturnVoid    (return-void))
  (Let           (let Name Expr))
  (Value         (| StrGet Literal Name))
  (StrGet        (str-get IntLiteral))
  (Literal       (| BoolLiteral IntLiteral))
  (IntLiteral    (#int))
  (BoolLiteral   (#bool))
  (String        (#string))
  (Name          (#name))
  (Types         (types (* Type)))
  (Type          (#type))
  (Params        (params (* Param)))
  (Param         (#name Type))
  (Expr          (| Call MathBinop Icmp Load Index Cast Value))
  (MathBinop     (| Add))
  (Icmp          (| LT LE GT GE EQ NE))
  (LT            ($binop <))
  (LE            ($binop <=))
  (GT            ($binop >))
  (GE            ($binop >=))
  (EQ            ($binop ==))
  (NE            ($binop !=))
  (Load          (Load Type Expr))
  (Index         (index Expr Type Expr))
  (Cast          (cast Type Type Expr))
  (Add           ($binop +))
  (Call          (| CallBasic CallVargs CallTail))
  (CallBasic     (call Name Types Type Args))
  (CallVargs     (call-vargs Name Types Type Args))
  (CallTail      (call-tail Name Types Type Args))
  (Args          (args (* Expr)))
)