/**
 * @file Constants.h
 * @brief This file defines the constant values used throughout the Pong game.
 *
 * It includes constants for window dimensions, ball properties, and paddle properties.
 */
#pragma once

/// The width of the game window in pixels.
const float WINDOW_WIDTH  = 1280;
/// The height of the game window in pixels.
const float WINDOW_HEIGHT = 720;

/// The width of the ball in pixels.
const float BALL_WIDTH    = 15;
/// The height of the ball in pixels.
const float BALL_HEIGHT   = 15;
/// The speed of the ball in pixels per millisecond.
const float BALL_SPEED    = 20.0f;

/// The width of the paddles in pixels.
const int PADDLE_WIDTH   = 10;
/// The height of the paddles in pixels.
const int PADDLE_HEIGHT  = 80;
/// The speed of the paddles in pixels per millisecond.
const float PADDLE_SPEED = 8.0f;
/// The x-coordinate of the first paddle.
const int PADDLE_ONE_X   = 50.0f;
/// The x-coordinate of the second paddle.
const int PADDLE_TWO_X   = WINDOW_WIDTH - PADDLE_ONE_X;