# -*- coding: utf-8 -*-
"""
Created on Wed Mar 14 19:12:15 2018

Different types of simple simulations that show the properties of optical flow control for landing.

Based on:
de Croon, G.C.H.E. (2016). Monocular distance estimation with optical flow maneuvers
and efference copies: a stability-based strategy. Bioinspiration & biomimetics, 11(1), 016004.

@author: Guido de Croon.
"""

from scipy.integrate import ode
import numpy as np
import matplotlib.pyplot as plt

# supporting functions:

def f_perfect_measurements(t, x):
    err = desired_div - (x[1] / x[0]);
    u = P * err;
    return [x[1], u];

def f_ZOH(t, x, arg1):
    u = arg1;
    return [x[1], u];

def free_fall(t,x):
    return[x[1], -9.8];

# Perfect measurements: literally the most perfect measurement, continuous, instead of from e.g. a camera
# Directly from state (see f_perfect_measurements)
def control_with_perfect_measurements():
    r = ode(f_perfect_measurements).set_integrator('zvode', method='bdf')  # why ode? to get the best continuous output
    r.set_initial_value(x0, t0)
    states_over_time = np.zeros([n_time_steps, n_states]);
    for t_index, t in enumerate(time_steps):
        x = r.integrate(r.t+dt);
        states_over_time[t_index, :] = x;

    return states_over_time;

# Zero-Order Hold
def control_with_ZOH():
    r = ode(f_ZOH).set_integrator('zvode', method='bdf')
    r.set_initial_value(x0, t0)
    states_over_time = np.zeros([n_time_steps, n_states]);
    for t_index, t in enumerate(time_steps):
        if(t_index >= 1):
            err = desired_div - (states_over_time[t_index-1, 1] / states_over_time[t_index-1, 0]);
        else:
            err = 0;
        u = P * err;
        r.set_f_params(u);
        x = r.integrate(r.t+dt);
        states_over_time[t_index, :] = x;

    return states_over_time;

def control_with_delay(time_steps_delay=3):
    r = ode(f_ZOH).set_integrator('zvode', method='bdf')
    r.set_initial_value(x0, t0)
    states_over_time = np.zeros([n_time_steps, n_states]);
    for t_index, t in enumerate(time_steps):
        if(t_index >= time_steps_delay+1):
            err = desired_div - (states_over_time[t_index-time_steps_delay-1, 1] / states_over_time[t_index-time_steps_delay-1, 0]);
        else:
            err = 0;
        u = P * err;
        r.set_f_params(u);
        x = r.integrate(r.t+dt);
        states_over_time[t_index, :] = x;

    return states_over_time;

def plot_states_over_time(states_over_time, time_steps, plot_title=''):
    plt.figure();
    plt.plot(time_steps, states_over_time[:,0], label='z');
    plt.plot(time_steps, states_over_time[:,1], label='v_z');
    plt.legend();
    if(plot_title != ''):
        plt.title(plot_title);

    plt.figure();
    plt.plot(time_steps, np.divide(states_over_time[:,1],states_over_time[:,0]), label='divergence');
    plt.plot([time_steps[0], time_steps[-1]], [desired_div, desired_div], '--', label='desired divergence');
    plt.legend();
    if(plot_title != ''):
        plt.title(plot_title);

    plt.show()


# ********************************************************
# TODO: Try out all three different types of 'simulations'
# ********************************************************

PERFECT_MEASUREMENTS = True;
ZOH = True;
DELAY = True;

# ************************************************************
# TODO: play around with initial state and desired divergence:
# ************************************************************

x0 = [10.0, 2.0]
desired_div = x0[1] / x0[0];  # if higher than initial -> first accelerate

# **********************************
# TODO: play around with the gain P:
# **********************************
P = 5 ;

# *************************************
# TODO: play around with the time step:
# *************************************
dt = 0.033;  # to get better results for ZOH/delay -> smaller time step to let instability happen later


# global variables:
n_states = 2;
t0 = 0;
t1 = 40;
time_steps = np.arange(t0, t1, dt);
n_time_steps = len(time_steps);


if(PERFECT_MEASUREMENTS):
    # control with perfect measurements:
    states_over_time = control_with_perfect_measurements();
    plot_states_over_time(states_over_time, time_steps, plot_title='control with perfect measurements')

if(ZOH):
    # control with ZOH:
    states_over_time = control_with_ZOH();
    plot_states_over_time(states_over_time, time_steps, plot_title='control with zero-order-hold')

if(DELAY):
    # control with delay:
    states_over_time = control_with_delay(time_steps_delay = 3);
    plot_states_over_time(states_over_time, time_steps, plot_title='control with delay')

