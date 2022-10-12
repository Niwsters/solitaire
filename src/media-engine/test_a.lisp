(defun hello-lisp ()
  (format t "hello-lisp!~%")
  :foo)

(defun receive-message (msg)
  (format t "~A~%" msg))
