#ifndef STATE__HPP
#define STATE__HPP

#include "state.hpp"

namespace state {
    enum Typeld {
        /// Or Wall
        BLOCK = 1,
        SPACE = 2,
        ROBOT = 3
    };
}

namespace state {
    class Element {
        // Associations
            state::Typeld typeElement;
        // Attributes
        protected :
            int x = 0;
            int y = 0;
        // Operations
        public :
            addElement ();
            subElement ();
            virtual getTypeID (TypeId const) = 0;
    };
}

namespace state {
    enum Direction {
        NONE = 0,
        EAST = 1,
        NORTH = 2,
        WEST = 3,
        SOUTH = 4
    };
}

namespace state {
    enum RobotStatus {
        NORMAL = 1,
        SHIELD = 2,
        DEAD = 3
    };
}

namespace state {
    class Robot : public state::Element {
        // Associations
            state::Direction direction;
            state::RobotStatus robotStatus;
        // Attributes
        protected :
            int speed;
        public :
            int position;
            int color;
            int shieldTime = 0;
            tab (x,y,visited) visitedCheckpoints;
            bool OwnsHeal;
            bool OwnsAutoAttack;
            bool OwnsShield;
            bool OwnsCrossAttack;
            bool OwnsBomb;
        // Operations
            Robot ();
            bool const isRobot ();
            TypeId const getTypeId ();
    };
}

namespace state {
    class StaticElement : public state::Element {
        // Operations
        public :
            bool isStatic ();
            virtual bool isEmpty () = 0;
    };
}

namespace state {
    class Block : public state::StaticElement {
        // Operations
        public :
            bool isEmpty ();
            TypeId getTypeId ();
            bool equals ( );
    };
}

namespace state {
    enum SpaceTypeid {
        NORMAL_TILE,
        START,
        CHECKPOINT,
        HOLE,
        BONUS,
        CONVBELT,
        ROT_CLK,
        ROT_ACLK,
        CB_N,
        CB_E,
        CB_S,
        CB_W,
        CB_N_E,
        CB_N_W,
        CB_E_N,
        CB_E_S,
        CB_S_E,
        CB_S_W,
        CB_W_N,
        CB_W_S,
        CB_NW_E,
        BONUS_EMPTY,
        BONUS_HEAL,
        BONUS_AUTO_ATTACK,
        BONUS_SHIELD,
        BONUS_CROSS_ATTACK,
        BONUS_BOMB
    };
}

namespace state {
    class Space : public state::StaticElement {
        // Associations
            state::SpaceTypeid spaceType;
        // Operations
        public :
            Space (SpaceTypeId id);
            bool isEmpty ();
            TypeId getTypeId ();
            SpaceTypeId getSpaceTypeId ();
            void setSpaceTypeId (SpaceTypeId id);
    };
}

namespace state {
    class ElementTab {
        // Associations
            state::Element element;
        // Attributes
        private :
            size_t width;
            size_t height;
            std::vector<std::vector<std::unique_ptr<Element>>> 2dTab;
        // Operations
        public :
            ElementTab (size_t width = 0, size_t height = 1);
            size_t getWidth ();
            size_t getHeight ();
            size_t add (Element* e);
            void resize (size_t width, size_t height);
            Element* get (int i, int j = 0);
            void set (int i, int j = 0, Element* e);
    };
}

namespace state {
    class State {
        // Associations
            state::ElementTab state;
        // Attributes
        private :
            state::ElementTab grid;
            state::ElementTab chars;
        // Operations
        public :
            ElementTab& getGrid ();
            ElementTab& getChars ();
    };
}

namespace state {
    class ElementFactory {
        // Operations
        public :
            ~ElementFactory ();
            virtual Element * newInstance (char id) = 0;
    };
}

namespace state {
    /**
     * \brief ID : typnamr
     *        E : Class
     */
    class ElementAlloc {
        // Attributes
        public :
             id;
        // Operations
            ElementAlloc ();
    };
}

#endif
