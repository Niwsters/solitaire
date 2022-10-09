(defpackage :logic
  (:use :cl)
  (:export :send-card :start-loop))
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

(defun send (msg)
  (with-open-file (fifo "./pipe-test"
                        :direction :output
                        :if-exists :supersede)
    (format fifo msg)))

(defun message (suit value)
  (concatenate
    'string
    (write-to-string (suit-to-num suit))
    " "
    (write-to-string (value-to-num value))
    " 30 50"))

(defun with-length (message)
  (concatenate
    'string
    (write-to-string (length message))
    " "
    message))

(defun send-card (suit value)
  (let ((msg (message suit value)))
    (print (concatenate 'string "sending: " msg))
    (send msg)))

(defun start-loop ()
  (loop
    (send-card :hearts :king)
    (sleep 1/60)))