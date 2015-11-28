#lang racket

(define (good_enough guess x)
  (< (abs (- (* guess guess guess) x)) 0.001))

(define (improve guess x)
  (/ (+ (/ x (* guess guess)) (* 2 guess)) 3))

(define (cube_root_iter guess x)
  (if (good_enough guess x)
      guess
      (cube_root_iter (improve guess x)
                      x)))

(define (cube_root x)
  (cube_root_iter 1.0 x))