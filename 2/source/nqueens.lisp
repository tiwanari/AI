;;; 参考URL:
;;; http://winnie.kuis.kyoto-u.ac.jp/~okuno/Lecture/02/AI/ai-02-9-ohp.pdf

;;; N-QUEENS
(defun n-queens (n &aux goal goals last-goals classes
  class classes-backup assumption solutions)
  ; added (it didn't init atms)
  (setq *atms* (create-atms "n-queens example"))
  (setq classes (make-class n)) ; creates assumptions
  (detect-capturing-pair classes) ; creates nogood
  (setq classes-backup classes)
  ; 仮説の検証
  (dotimes (i n)
    (setq goals nil)
    (setq class (pop classes-backup))
    (dotimes (j n)
      (setq assumption (pop class))
      (setq goal (tms-create-node *atms* (list 'queen i j)))
      (if (null last-goals) ; first row
        (justify-node 'first-row goal (list assumption))
        (dolist (previous-goal last-goals) 
          (justify-node 'compose goal (list previous-goal assumption))))
      (push goal goals))
    (setq last-goals goals))
  (setq solutions 
    (mapcan #'(lambda (x) (copy-tree (tms-node-label x))) goals))
  (length solutions)) ; show the number of solutions

(defun make-class (n &aux node class classes)
  (dotimes (row n)
    (setq class nil)
    (dotimes (column n)
      (push (setq node (tms-create-node *atms* `(Queen ,row ,column))) 
        class)
      (assume-node node))
    (push (nreverse class) classes))
  (nreverse classes))

(defun detect-capturing-pair (classes)
  (do ((class1 (pop classes) (pop classes)))
      ((null classes))
    (dolist (node1 class1)
      (dolist (class2 classes)
        (dolist (node2 class2)
          ; modified (node-datum does not exist)
          (if (queens-captured? (tms-node-datum node1) (tms-node-datum node2))
            ; modified (lack of arguments)
            (nogood-nodes *atms* (list node1 node2)) ))))))

(defun queens-captured? (q1 q2)
  (or (= (caddr q1) (caddr q2)) ; modified (it checked the same row, not column)
      (= (abs (- (cadr q1) (cadr q2))) (abs (- (caddr q1) (caddr q2))))))

; (defun n-queens-by-IC (n &aux classes solutions)
;   (setq *atms* (create-atms "n-queens example"))  ; added
;   (setq classes (make-class n))
;   (detect-capturing-pair classes)
;   (setq solutions
;     (interpretations *atms* classes))
;   (length solutions))
