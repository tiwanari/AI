;;; できませんでした〜！！！！



;;; ---------- User's program ----------
(setq *atms* (create-atms "alphametic"))

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

(defun calc-word (ls a b c d e)
  (+ (* (elt ls a) 10000)
     (* (elt ls b) 1000)
     (* (elt ls c) 100)
     (* (elt ls d) 10)
     (elt ls e)))

(defun solve-49 ()
  (dolist (ls (permutation 9 (iota 1 9)))
    (let ((wrong (calc-word ls 0 1 2 3 4))
          (right (calc-word ls 1 5 4 6 7))
          (m (elt ls 8)))
      (if (= (* wrong m) right)
          (format t "~D * ~D = ~D~%" wrong m right)))))