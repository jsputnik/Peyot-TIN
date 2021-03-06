//Peyot
//Iwo Sokal, Illia Yatskevich
//4.06.2021

#ifndef PEYOT_PARSER_H
#define PEYOT_PARSER_H


#include "LoginRequest.h"
#include "QuitRequest.h"
#include "RegisterRequest.h"
#include "BookRequest.h"
#include "ResignRequest.h"
#include "ModifyRequest.h"
#include "CheckMyTerminsRequest.h"
#include "CheckTerminsByInstructorRequest.h"
#include "Response.h"
#include "SetScheduleRequest.h"
#include "CheckInstructorsRequest.h"
#include <optional>
#include <memory>

class Parser {
    int current_index = 0;
    std::string message;
public:
    Parser() {}
    Parser(std::string message): message(message) {}
    std::unique_ptr<Request> parse_request();
    std::unique_ptr<QuitRequest> parse_quit_request();
    std::unique_ptr<LoginRequest> parse_login_request();
    std::unique_ptr<RegisterRequest> parse_register_request();
    std::unique_ptr<BookRequest> parse_book_request();
    std::unique_ptr<ResignRequest> parse_resign_request();
    std::unique_ptr<ModifyRequest> parse_modify_request();
    std::unique_ptr<CheckInstructorsRequest> parse_check_instructors_request();
    std::unique_ptr<CheckMyTerminsRequest> parse_check_my_termins_request();
    std::unique_ptr<CheckTerminsByInstructorRequest> parse_check_termins_by_instructor_request();
    std::unique_ptr<SetScheduleRequest> parse_setschedule_request();
    std::unique_ptr<Response> parse_response();
    std::optional<std::string> parse_keyword(std::string keyword);
    std::optional<std::string> parse_login();
    std::optional<std::string> parse_password();
    std::optional<std::string> parse_flag(std::string flag); //-mytermins, -instermins etc
    std::optional<std::string> parse_date(); //-mytermins, -instermins etc
    void init(std::string message);

    const std::string &getMessage() const;

    void setMessage(const std::string &message);

    int getCurrentIndex() const;

    void setCurrentIndex(int currentIndex);
};

#endif //PEYOT_PARSER_H
