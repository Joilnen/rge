#ifndef WORKAREA_H
#define WORKAREA_H


class WorkArea3D {

    WorkArea3D();
    public:
        static WorkArea3D& getInstance() {
            static WorkArea3D u;
            return u;
        }
        virtual ~WorkArea3D();

        void createWorkPlane();
};


#endif


