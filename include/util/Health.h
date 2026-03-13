#ifndef HEALTH_H
#define HEALTH_H

class Health {
    private:
        int current_;
        int max_; // default 100

    public:
        explicit Health(int maxHp = 100) : current_(maxHp), max_(maxHp) {}

        int current() const { return current_; }
        int max() const { return max_; }

        bool isFainted() const { return current_ <= 0; } // basically dead

        void damage(int amount) {
            if (amount < 0) amount = 0;
            current_ -= amount;
            if (current_ < 0) current_ = 0;
        }

        void heal(int amount) {
            if (amount < 0) amount = 0;
            current_ += amount;
            if (current_ > max_) current_ = max_;
        }

        void healToFull() {
            current_ = max_;
        }

        void changeMax(int amount) {
            max_ += amount;
            if (max_ < 1) { max_ = 1; }
            if (current_ > max_) { current_ = max_; }
        }

        void reset() {
            current_ = max_;
        }


        void set(int current, int max) {
            max_ = max;
            if (max_ < 1) { max_ = 1; }
            current_ = current;
            if (current_ > max_) { current_ = max_; }
            if (current_ < 0) { current_ = 0; }
        }
    };

#endif