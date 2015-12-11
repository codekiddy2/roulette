#pragma once

// PCH includes
// TODO: modify or add more includes here for faster compilation and intellisense according to your needs

#define _SCL_SECURE_NO_WARNINGS

DW // disable warnings macro (to compile own code with W4 flag)

// gtkmm
#include <gtkmm\gtkmm.h>
#include <sigc++\sigc++.h>
#include <glibmm\glibmm.h>
#include <cairomm\cairomm.h>
#include <atkmm\atkmm.h>
#include <pangomm\pangomm.h>
#include <goocanvasmm\goocanvasmm.h>


// boost
#include <boost/filesystem.hpp>
#include <boost/random.hpp>
#include <boost/random/random_device.hpp> // for random_device



// std
#include <string> // for to_string()


EW // enable warnings macro
