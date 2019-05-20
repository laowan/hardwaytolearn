#lang racket
(define (func x y z)
  (if (< x y)
      (if (< x z)
          (+ y z)
          (+ x y))
      (if (> y z)
          (+ x y)
          (+ x z))))