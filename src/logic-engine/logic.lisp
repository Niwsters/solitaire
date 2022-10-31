(defpackage :logic
  (:use :cl)
  (:export :receive-message :get-card :mouse-moved))
(in-package :logic)

(defun suit-to-num (suit)
  (case suit
    (:clubs 0)
    (:diamonds 1)
    (:hearts 2)
    (:spades 3)))

(defun value-to-num (value)
  (case value
    (:ace 0)
    (:two 1)
    (:three 2)
    (:four 3)
    (:five 4)
    (:six 5)
    (:seven 6)
    (:eight 7)
    (:nine 8)
    (:ten 9)
    (:jack 10)
    (:queen 11)
    (:king 12)))

(defun receive-message (msg)
  (ignore-errors (eval (read-from-string msg))))

(defun get-card ()
  (coerce (concatenate 'string
                       "1 10 50  50;"
                       "0 4  200 200;") 'base-string))

(defun list-to-str (lst)
  (format nil "~{~A~}" lst))

(defun str (&rest elems)
  (list-to-str
    (loop for elem in elems
      collect
        (typecase elem
          (string elem)
          (otherwise (write-to-string elem))))))

(defparameter state (make-hash-table))

(defun mouse-moved (x y)
  (setf (gethash 'mouse-pos state) (str x " " y)))
