
! module for testing creation of a Grid
module read_joana_module
  use grid_module
  implicit none
contains
    
  ! read_joanna_gg(grid)
  ! -----------------
 
  subroutine read_grid(g)
    type(Grid), intent(inout) :: g
    integer                   :: nnode
    integer                   :: nedge
    integer                   :: nface
    integer                   :: ncoin
    integer                   :: before1
    integer                   :: before2
    integer                   :: edge_cnt
    integer                   :: idx
    real                      :: vol
    integer                   :: p1,p2

    integer :: iface
    integer :: inode

    open(5,file='meshvol.d',access='sequential',status='old')

    read(5,*) nnode, nedge, nface, ncoin, before2, before1  !nbefore1<nbefore2

    ! Specify element type
    call g%init("LagrangeP1_Triag2D")
    
    g%nb_nodes = nnode
    g%nb_elems = 0 ! This mesh only contains edges *sad*
    g%nb_faces = nedge ! -(before2-before1+1)
    
    ! Fill in nodes and cells
    allocate(g%nodes(g%nb_nodes,g%dimension))
    do inode = 1, g%nb_nodes
      read(5,*) g%nodes(inode,1), g%nodes(inode,2), vol
    enddo

    edge_cnt = 0
    allocate(g%faces(g%nb_faces,2)) ! this 2 should be nb_nodes_per_face
    do iface = 1, g%nb_faces
      read(5,*) idx, p1, p2
      if (.true.) then
      !if (iface<before1 .or. iface>before2) then
        edge_cnt = edge_cnt + 1
        g%faces(edge_cnt,1) = p1
        g%faces(edge_cnt,2) = p2
      endif
    enddo
    g%nb_faces = edge_cnt
    
    close(5)
    
  end subroutine read_grid


  subroutine read_fields(g)
    type(Grid), intent(inout) :: g
    
    class(FunctionSpace),  pointer    :: vertices
    class(FunctionSpace),  pointer    :: faces

    type(Field),           pointer    :: V
    type(Field),           pointer    :: S

    integer                   :: nnode
    integer                   :: nedge
    integer                   :: nface
    integer                   :: ncoin
    integer                   :: before1
    integer                   :: before2
    integer                   :: edge_cnt
    integer                   :: idx
    real                      :: vol
    integer                   :: p1,p2
    integer :: dummy_int
    real    :: dummy_real
    integer :: iface
    integer :: inode
    integer :: n
    real :: Sx, Sy
    real :: pi,r,y,sm,hx,hy


    open(5,file='meshvol.d',access='sequential',status='old')
    read(5,*) nnode, nedge, nface, ncoin, before2, before1  !nbefore1<nbefore2

    ! Create a scalar field for the dual volume in the vertices
    vertices => new_ContinuousFunctionSpace("vertices","LagrangeP1", g)
    V     => vertices%add_scalar_field("dual_volume")

    do inode = 1, g%nb_nodes
      read(5,*) dummy_real, dummy_real, V%array(inode,1)
    enddo

    do iface = 1, nedge
      read(5,*) dummy_int, dummy_int, dummy_int
    enddo

    ! Setup a function space in the face centres for the face_normal
    faces => new_FaceFunctionSpace("faces", "LagrangeP0", g)
    S     => faces%add_vector_field("face_normal")

    edge_cnt = 0
    do iface = 1,nedge
      read(5,*) dummy_int, Sx, Sy
      if (.true.) then
      !if (iface<before1 .or. iface>before2) then
        edge_cnt = edge_cnt + 1
        S%array(edge_cnt,1) = Sx
        S%array(edge_cnt,2) = Sy
      endif
    enddo

    close(5)


    ! Coordinate transformation correction for dual_volume on sphere
    r=6371.22e+03
    pi=acos(-1.)
    do inode=1,g%nb_nodes
      y=g%nodes(inode,2)
      hx=r*cos(y)
      hy=r
     sm=hx*hy
     V%array(inode,1) = v%array(inode,1)*sm
   enddo

  end subroutine read_fields

  subroutine write_gmsh_nodal_field(g,name)
    type(Grid), intent(inout) :: g
    character(len=*) , intent(in) :: name
    class(FunctionSpace),  pointer    :: vertices
    class(Field),  pointer            :: F
    integer :: inode
    vertices => g%function_space("vertices")
    F => vertices%field(name)
    write(50,'(A)')"$NodeData"
    write(50,*) 1                     ! one string tag:
    write(50,'(A)') '"'//F%name//'"'      ! the name of the view ("A scalar view")
    write(50,*) 1                     ! one real tag:
    write(50,*) 0.0                   ! the time value (0.0)
    write(50,*) 3                     ! three integer tags:
    write(50,*) 0                     ! the time step (0; time steps always start at 0)
    if (F%cols == 1) write(50,*) 1    ! 1-component (scalar) field
    if (F%cols == 2) write(50,*) 3    ! 3-component (vector) field
    write(50,*) g%nb_nodes            ! number of associated nodal values
    do inode=1,g%nb_nodes
      if (F%cols == 1) write(50,*) inode, F%array(inode,1)
      if (F%cols == 2) write(50,*) inode, F%array(inode,1), F%array(inode,2), 0     
    enddo
    write(50,'(A)')"$EndNodeData"
  end subroutine write_gmsh_nodal_field

  subroutine write_gmsh_face_field(g,name)
    type(Grid), intent(inout) :: g
    character(len=*) , intent(in) :: name
    class(FunctionSpace),  pointer    :: faces
    class(Field),  pointer            :: F
    integer :: iface
    faces => g%function_space("faces")
    F => faces%field(name)
    write(50,'(A)')"$ElementData"
    write(50,*) 1                     ! one string tag:
    write(50,'(A)') '"'//F%name//'"'      ! the name of the view ("A scalar view")
    write(50,*) 1                     ! one real tag:
    write(50,*) 0.0                   ! the time value (0.0)
    write(50,*) 3                     ! three integer tags:
    write(50,*) 0                     ! the time step (0; time steps always start at 0)
    if (F%cols == 1) write(50,*) 1    ! 1-component (scalar) field
    if (F%cols == 2) write(50,*) 3    ! 3-component (vector) field
    write(50,*) g%nb_faces            ! number of associated nodal values
    do iface=1,g%nb_faces
      if (F%cols == 1) write(50,*) iface, F%array(iface,1)
      if (F%cols == 2) write(50,*) iface, F%array(iface,1), F%array(iface,2), 0     
    enddo
    write(50,'(A)')"$EndElementData"
  end subroutine write_gmsh_face_field

  subroutine write_gmsh(g)
    type(Grid), intent(inout) :: g
    integer :: iface, inode
    write(0,*) "Writing Gmsh file meshvol.msh"
    open(50,file='meshvol.msh',access='sequential',status='REPLACE')
    write(50,'(A)')"$MeshFormat"
    write(50,'(A)')"2.2 0 8"
    write(50,'(A)')"$EndMeshFormat"
    write(50,'(A)')"$Nodes"
    write(50,*)g%nb_nodes
    do inode=1,g%nb_nodes
      write(50,*) inode, g%nodes(inode,1), g%nodes(inode,2), 0
    enddo
    write(50,'(A)')"$EndNodes"
    write(50,'(A)')"$Elements"
    write(50,*) g%nb_faces
    do iface=1, g%nb_faces
      ! element-number  type(1=lineP1)  nb_tags(=2)  tag1(=physical-group)  tag2(=elementary-group)  [nodes]
      write(50,*)  iface, 1, 2, 1, 1, g%faces(iface,1), g%faces(iface,2)
    enddo
    write(50,'(A)')"$EndElements"
    call write_gmsh_nodal_field(g,"dual_volume")
    call write_gmsh_face_field(g,"face_normal")
    call write_gmsh_nodal_field(g,"velocity")
    call write_gmsh_nodal_field(g,"height")
    close(50)
  end subroutine write_gmsh
  
  subroutine initial_solution_rossby_haurwitz(function_space)
    class(FunctionSpace),  pointer, intent(in)    :: function_space
    class(Field),  pointer            :: P, U
    integer :: inode


    real :: aaa0,zk
    integer :: IR,ip
    real :: om,ph0,g,ath,bth,cth,pi,f0,x,y,th,a,cor

    data OM,ZK,IR,PH0/7.848E-6,7.848E-6,4,78.4E3/
    data G/9.80616/

    ATH(TH) = OM*0.5*(F0+OM)*(cos(TH))**2 &
      & +0.25*ZK**2*(cos(TH))**(2*IR)*( (IR+1)*(cos(TH))**2 &
      & +FLOAT(2*IR**2-IR-2)-2.*IR**2/(cos(TH))**2 )
    BTH(TH) = (F0+2.*OM)*ZK/FLOAT((IR+1)*(IR+2))*(cos(TH))**IR &
      & *( FLOAT(IR**2+2*IR+2)-((IR+1)*cos(TH))**2 )
    CTH(TH) = 0.25*ZK**2*(cos(TH))**(2*IR)*( FLOAT(IR+1)*(cos(TH))**2 &
      & -FLOAT(IR+2) )  

    P => function_space%add_scalar_field("height")
    U => function_space%add_vector_field("velocity")

    aaa0=0.
    a = 6371.22e+03 ! Earth radius

    pi = acos(-1.)
    f0 = 1.4584e-04 !coriolis parameter (=2xearth's omega)
    do inode=1,function_space%g%nb_nodes
      x=function_space%g%nodes(inode,1)
      y=function_space%g%nodes(inode,2)
      if(x == 2.*pi) x=0.
        cor=F0*sin(y)
        U%array(inode,1) =  A*OM*cos(y)+A*ZK*cos(IR*x) &
          &       *(cos(y))**(IR-1)*(IR*(sin(y))**2-(cos(y))**2)
        U%array(inode,2) = -A*ZK*IR*(cos(y))**(IR-1)*sin(Y)*sin(IR*x)
        P%array(inode,1) = ( PH0+A**2*ATH(y)+A**2*BTH(y)*cos(IR*x) &
          &       +A**2*CTH(y)*cos(2.*IR*x) ) / g
        P%array(inode,1) = max(aaa0,P%array(inode,1))
        U%array(inode,1) = U%array(inode,1) * P%array(inode,1)
        U%array(inode,2) = U%array(inode,2) * P%array(inode,1)
        if(y == 0.5*pi) U%array(inode,1)=0.
        if(y ==-0.5*pi) U%array(inode,1)=0.
    enddo

  end subroutine initial_solution_rossby_haurwitz

end module read_joana_module

! =============================================================================
! =============================================================================
! =============================================================================

! Main program
program main
  use grid_module
  use read_joana_module
  implicit none
  
  ! Declarations
  ! ------------
  type(Grid)                        :: g
  class(FunctionSpace),  pointer    :: vertices
  class(FunctionSpace),  pointer    :: faces
  class(Field),  pointer            :: V
  class(Field),  pointer            :: S
  class(Field),  pointer            :: U
  class(Field),  pointer            :: P


  ! Execution
  ! ---------
  
  call read_grid(g)
  call read_fields(g)

  vertices => g%function_space("vertices")
  faces    => g%function_space("faces")

  V => vertices%field("dual_volume")
  S => faces%field("face_normal")

  call initial_solution_rossby_haurwitz(vertices)
  U => vertices%field("velocity")
  P => vertices%field("height")

  call write_gmsh(g)

  ! Destruction
  ! -----------
  ! Recursively deallocate the grid, functionspaces, fields, ...
  call g%destruct()

end program main