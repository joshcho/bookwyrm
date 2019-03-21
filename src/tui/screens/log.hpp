#pragma once

#include <optional>

#include "plugin_handler.hpp"
#include "screens/base.hpp"

namespace bookwyrm::tui::screen {

    class log : public base {
    public:
        explicit log(const core::log_level wanted_level, std::function<bool(void)> &&predicate);

        void paint() override;
        void toggle_action() override;
        void move(move_direction dir) override;

        std::string footer_info() const override;
        int scrollpercent() const override;
        inline std::string controls_legacy() const override { return "[j/k d/u]Navigation [SPACE]attach/detach"; }

        void log_entry(core::log_level level, std::string msg);

        std::optional<core::log_level> worst_unread() const;
        std::vector<core::log_pair> unread_logs() const;

    private:
        const core::log_level wanted_level_;
        std::function<bool(void)> is_log_focused_;

        std::vector<core::log_pair> entries_;
        std::vector<core::log_pair> unread_entries_;

        using log_pp = decltype(entries_.cbegin());
        std::optional<log_pp> detached_at_;

        /*
         * Returns the amount of entries in entries_ (starting at the last entry)
         * that can fit on screen.
         */
        size_t capacity(log_pp entry) const;

        void print_entry(int &y, const log_pp entry);
    };

} // namespace bookwyrm::tui::screen
