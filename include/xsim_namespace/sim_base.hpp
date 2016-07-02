#ifndef SIM_BASE_HPP_INCLUDED
#define SIM_BASE_HPP_INCLUDED

class SimBase
{
    XSIM_NONCOPYABLE_CLASS(SimBase)

private:
    struct SimBasePrivate;
    std::shared_ptr<SimBasePrivate> d_ptr;

public:
    typedef std::vector<SimBase*> object_array;

private:
    void            Init();

    void            AddChild(SimBase* child);
    void            RemoveChild(SimBase* child);

protected:
    virtual ~SimBase();
    SimBase(const string_t& name, SimBase* parent = 0);
    SimBase(const char* name, SimBase* parent = 0);

    object_array&   GetChildren();
    SimBase*        GetParent();
    SimBase*        FindChildByName(const string_t& name);
    u32_t           FindChild(SimBase* obj);

    void            AttachTo(SimBase* obj);
    void            DetachFrom(SimBase* obj);

public:
    const string_t& GetObjectName() const;
    void            SetObjectName(const string_t& name);
    void            SetObjectName(const char*     name);
};

#endif // SIM_BASE_HPP_INCLUDED
