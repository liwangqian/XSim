#ifndef SIM_BASE_IMPL_HPP_INCLUDED
#define SIM_BASE_IMPL_HPP_INCLUDED

struct SimBase::SimBasePrivate
{
    string_t        name;
    object_array    children;
    SimBase*        parent;
};

/** @brief (one liner)
  *
  * (documentation goes here)
  */
void SimBase::Init()
{
    d_ptr = std::make_shared<SimBasePrivate>();
    d_ptr->parent = nullptr;
}

SimBase::~SimBase()
{
    xsim_extra_debug_sigprint_this(this);
    if (d_ptr->parent)
    {
        DetachFrom(d_ptr->parent);
        d_ptr->parent = nullptr;
    }

    //从后往前删除：先创建的对象后删除
    auto iter = d_ptr->children.rbegin();
    while (iter != d_ptr->children.rend())
    {
        delete *iter;
        ++iter;
    }
}

/** @brief (one liner)
  *
  * (documentation goes here)
  */
void SimBase::DetachFrom(SimBase* obj)
{
    xsim_extra_debug_sigprint();
    obj->RemoveChild(this);
}

/** @brief (one liner)
  *
  * (documentation goes here)
  */
void SimBase::AttachTo(SimBase* obj)
{
    xsim_extra_debug_sigprint();
    obj->AddChild(this);
}

/** @brief (one liner)
  *
  * (documentation goes here)
  */
void SimBase::SetObjectName(const char* name)
{
    if (name != 0)
        d_ptr->name.assign(name);
}

/** @brief (one liner)
  *
  * (documentation goes here)
  */
void SimBase::SetObjectName(const string_t& name)
{
    d_ptr->name = name;
}

/** @brief (one liner)
  *
  * (documentation goes here)
  */
const string_t & SimBase::GetObjectName() const
{
    return d_ptr->name;
}

/** @brief (one liner)
  *
  * (documentation goes here)
  */
 SimBase::SimBase(const char* name, SimBase* parent)
{
    xsim_extra_debug_sigprint_this(this);
    Init();

    d_ptr->name.assign(name);
    d_ptr->parent = parent;

    if (parent)
    {
        AttachTo(parent);
    }
}

/** @brief (one liner)
  *
  * (documentation goes here)
  */
 SimBase::SimBase(const string_t& name, SimBase* parent)
{
    xsim_extra_debug_sigprint_this(this);
    Init();

    d_ptr->name = name;
    d_ptr->parent = parent;

    if (parent)
    {
        AttachTo(parent);
    }
}

/** @brief (one liner)
  *
  * (documentation goes here)
  */
SimBase* SimBase::FindChildByName(const string_t& name)
{
    for (auto &x : d_ptr->children)
    {
        if (x->d_ptr->name == name)
        {
            return x;
        }
    }

    return nullptr;
}

/** @brief (one liner)
  *
  * (documentation goes here)
  */
u32_t SimBase::FindChild(SimBase* obj)
{
    const u32_t size = d_ptr->children.size();
    for (u32_t id = 0; id < size; ++id)
    {
        if (d_ptr->children[id] == obj)
        {
            return id;
        }
    }

    return XSIM_INDEX_INVALID;
}



/** @brief (one liner)
  *
  * (documentation goes here)
  */
SimBase* SimBase::GetParent()
{
    return d_ptr->parent;
}

/** @brief (one liner)
  *
  * (documentation goes here)
  */
SimBase::object_array & SimBase::GetChildren()
{
    return d_ptr->children;
}

/** @brief (one liner)
  *
  * (documentation goes here)
  */
void SimBase::RemoveChild(SimBase* child)
{
    xsim_extra_debug_sigprint();
    auto iter = d_ptr->children.begin();
    while (iter != d_ptr->children.end())
    {
        if (*iter == child)
        {
            d_ptr->children.erase(iter);
            break;
        }
        iter++;
    }
}

/** @brief (one liner)
  *
  * (documentation goes here)
  */
void SimBase::AddChild(SimBase* child)
{
    xsim_extra_debug_sigprint();
    d_ptr->children.push_back(child);
}



#endif // SIM_BASE_IMPL_HPP_INCLUDED
