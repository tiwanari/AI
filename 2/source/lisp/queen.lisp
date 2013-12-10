(create-atms title
	&key (node-string 'default-node-string)
		(debugging nil)
		(enqueue-procedure nil))

(change-atms atms &key node-string debugging enqueue-procedure)

(tms-create-node atms node-datum &key assumptionp contradictionp)

(interpretations atms choice-sets &optional defaults)

(in-antecedent? antecedents?)

(supporting-antecedent? node env)

(setq *atms* (create-atms "Simple Example"))

(setq assumption-a (tms-create-node *atms* "A" :ASSUMPTIONP t)
	assumption-c (tms-create-node *atms* "C" :ASSUMPTIONP t)
	assumption-e (tms-create-node *atms* "E" :ASSUMPTIONP t))

(setq node-h (tms-create-node *atms* "h"))

(justify-node "R1" node-h (list assumption-c assumption-e))

(why-node node-h)

(setq node-g (tms-create-node *atms* "g"))
(justify-node "R2" node-g (list assumption-a assumption-c))
(setq contradiction (tms-create-node *atms* 'CONTRA :CONTRADICTORYP t))
(justify-node "R3" contradiction (list node-g))
(mapc #'print-env (interpretations *atms* nil (atms-assumptions *atms*)))

(defun n-queens (n &aux goal goals last-goals classes
	class classes-backup assumption solutions)
	(setq classes (make-class n))	; 仮定の作成
	(detect-capturing-pair classes)	; nogoodの作成
	(setq classes-backup classes)
	(dotimes (i n)
			(setq goals nil)
			(setq class (pop classes-backup))
			(dotimes (j n)
				(setq assumption (pop class))
				(setq goal (tms-create-node *atms* (list 'queen i j)))
				(if (null last-goals)	; 第1行目かどうか
					(justify-node 'first-row goal (list assumption))
					(dolist (previous-goal last-goals)
						(justify-node 'compose goal (list previous-goal assumption))))
				(push goal goals))
		(setq last-goals goals))
	(setq solutions (mapcan #'(lambda (x) (copy-tree (tms-node-label x))) goals))
	(length solutions))	; 最終行のラベル答えが

(defun make-class (n &aux node class classes)
	(dotimes (row n)
		(setq class nil)
		(dotimes (column n)
			(push (setq node (tms-create-node *atms* '(Queen, row, column))) class)
			(assume-node node))
		(push (nreverse class) classes))
	(nreverse classes))

(defun detect-capturing-pair (classes)
	(do ((class1 (pop classes) (pop classes)))
		((null classes))
		(dolist(node1 class1)
			(dolist (class2 classes)
				(dolist (node2 class2)
					(if (queens-captured? (node-datum node1) (node-datum node2))
						(nogood-nodes (list node1 node2)) ))))))

(defun queens-captured? (q1 q2)
	(or (= (cadr q1) (cadr q2))
		(= (abs (- (cadr q1) (cadr q2))) (abs (- (caddr q1) (caddr q2))))))

(ext:saveinitmem "hello-clisp"
                 :quiet t               ; バナーを表示しない
                 :norc t                ; 初期化ファイルをロードしない
                 :init-function #'hello ; REPLの前にhelloを呼ぶ
                 :executable t)