/*
 * Copyright (c) 2012 Aldebaran Robotics. All rights reserved.
 * Use of this source code is governed by a BSD-style license that can be
 * found in the COPYING file.
 */

#ifndef LIBQI_APPLICATION_HPP_
#define LIBQI_APPLICATION_HPP_

#include <boost/function.hpp>
#include <qi/api.hpp>
#include <qi/macro.hpp>
#include <vector>

namespace qi {

  class QI_API Application
  {
  public:
    Application(int& argc, char** &argv);
    ~Application();

    static void run();
    static void stop();

    static const std::vector<std::string>& arguments();
    static int argc();
    static const char** argv();
    static void setName(const std::string &name);
    static std::string name();
    static void setArguments(int argc, char** argv);
    static void setArguments(const std::vector<std::string>& arguments);

    static void* loadModule(const std::string& name, int flags=-1);
    static void unloadModule(void* handle);
    static bool initialized();

    static const char* program();

    static bool atEnter(boost::function<void()> func);
    static bool atExit(boost::function<void()> func);
    static bool atStop(boost::function<void()> func);
    static bool atSignal(boost::function<void(int)> func, int signal);
  };
}

#define QI_AT_ENTER(func) \
static bool QI_UNIQ_DEF(_qi_atenter) = ::qi::Application::atEnter(func);

#define QI_AT_EXIT(func) \
static bool QI_UNIQ_DEF(_qi_atexit) = ::qi::Application::atExit(func);

//THIS IS INTERNAL
//API is not maintained for this function
#define _QI_COMMAND_LINE_OPTIONS(desc, opts)                          \
static void QI_UNIQ_DEF(_qi_opt_func)() {                             \
  namespace po = boost::program_options;                              \
  po::variables_map vm;                                               \
  po::command_line_parser p(::qi::Application::arguments());          \
  po::options_description options(desc);                              \
  {                                                                   \
    using namespace boost::program_options;                           \
    options.add_options() opts;                                       \
  }                                                                   \
  options.add_options()                                               \
    ("help,h", "Show command line options")                           \
    ("__positional", po::value<std::vector<std::string> >(),          \
      "Positional arguments");                                        \
  po::positional_options_description pos;                             \
  pos.add("__positional", -1);                                        \
  po::parsed_options res = p.options(options)                         \
    .allow_unregistered()                                             \
    .positional(pos)                                                  \
    .run();                                                           \
  po::store(res, vm);                                                 \
  /* Invoke notify callbacks*/                                        \
  po::notify(vm);                                                     \
  if (vm.count("help"))                                               \
    std::cout << options << std::endl;                                \
  std::vector<std::string> args                                       \
    = po::collect_unrecognized(res.options, po::include_positional);  \
  /* Keep --help for next option parser*/                             \
  if (vm.count("help"))                                               \
    args.push_back("--help");                                         \
  /* Set arguments to what was not used */                            \
  ::qi::Application::setArguments(args);                              \
}                                                                     \
QI_AT_ENTER(boost::bind(&(QI_UNIQ_DEF(_qi_opt_func))))


#endif
