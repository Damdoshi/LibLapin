#!/bin/sh
clear
echo "## ----------------------------------------------------------------------------- ##"
sleep 0.03
echo "## -- HANGED BUNNY STUDIO 2014-2016 ------- ---   -   --- ---- --  --   - --- -- ##"
sleep 0.03
echo "## ---Jason Brillante \"Damdoshi\"----------- ---- --- - -- --- - - - -- --  -- -- ##"
sleep 0.03
echo "## ---Les Lapins Noirs -------------------- ---- --- - -- --- - - - -- --  -- -- ##"
sleep 0.03
echo "## ---------------------------------------- ---- --- - -- --- - - - -- --  -- -- ##"
sleep 0.03
echo "## -----|\-//------------------------------ ---- ---   -- --- - -  --- -- - - -- ##"
sleep 0.03
echo "## -----||//___---------------------------- ---- --- - -- ---   - ---- -- - - -- ##"
sleep 0.03
echo "## ----O  /    \--------------------------- ---- --- - -- --- - - ---- -- --  -- ##"
sleep 0.03
echo "## ---<________/---------------------------   -   -   ---   - - - ---   - --- -- ##"
sleep 0.03
echo "## ----------------------------------------------------------------------------- ##"
sleep 0.03
echo "## ----------------------------------------------------------------------------- ##"
sleep 0.03
echo "## ----------------------------------------------------------------------------- ##"
sleep 0.03
echo "## ----------------------------------------------------------------------------- ##"
sleep 0.03
echo "## ----------------------------------------------------------------------------- ##"
sleep 0.03
echo "## ----------------------------------------------------------------------------- ##"

INCLUDE_DIR=${HOME}/.froot/include
LIB_DIR=${HOME}/.froot/lib

echo "Targets are ${INCLUDE_DIR} and ${LIB_DIR}"

get_out()
{
    echo $1
    exit
}

test_and_add_bash()
{
    if [ -e $1 ] ; then
	FROOT=`grep "${INCLUDE_DIR}" $1`
	if [ -z "${FROOT}" ]; then
	    echo "" >> $1
	    echo 'export LD_LIBRARY_PATH="${LIB_DIR}"' >> $1
	    echo 'export C_INCLUDE_PATH=\"${INCLUDE_DIR}"' >> $1
	    echo 'export CPLUS_INCLUDE_PATH=\"${INCLUDE_DIR}"' >> $1
	fi
    fi
}

test_and_add_csh()
{
    if [ -e $1 ] ; then
	FROOT=`grep "${INCLUDE_DIR}" $1`
	if [ -z "${FROOT}" ]; then
	    echo "" >> $1
	    echo 'setenv LD_LIBRARY_PATH "${LIB_DIR"' >> $1
	    echo 'setenv C_INCLUDE_PATH "${INCLUDE_DIR}"' >> $1
	    echo 'setenv CPLUS_INCLUDE_PATH "${INCLUDE_DIR}"' >> $1
	fi
    fi
}

mkdir -p ${LIB_DIR} ${INCLUDE_DIR}		|| get_out "Failed to create installation directories."

# Dependancies
cp -r external/include/* ${INCLUDE_DIR}		|| get_out "Failed to install dependancies headers."
cp external/lib/* ${LIB_DIR}			|| get_out "Failed to install dependancies binaries."

make						|| get_out "No bunnies were build. Make failed."

# Bunnies
cp -r include/* ${INCLUDE_DIR}		|| get_out "Failed to install Lapin headers."
cp liblapin.a lib/ ${LIB_DIR}			|| get_out "Failed to install Lapin binaries."

chmod 644 ${INCLUDE_DIR}*.h*			|| get_out "Failed to change mode of headers."
chmod 644 ${INCLUDE_DIR}*/*.h*		|| get_out "Failed to change mode of headers."
chmod 644 ${INCLUDE_DIR}*/*/*.h*		|| get_out "Failed to change mode of headers."
chmod 644 ${LIB_DIR}/*.a			|| get_out "Failed to change mode of binaries."
chmod 755 ${LIB_DIR}/*.so			|| get_out "Failed to change mode of binaries."

# "LDCONFIG"

ln -fs ${LIB_DIR}/libsfml-audio.so ${LIB_DIR}/libsfml-audio.so.2.3 && \
    ln -fs ${LIB_DIR}/libsfml-graphics.so ${LIB_DIR}/libsfml-graphics.so.2.3 && \
    ln -fs ${LIB_DIR}/libsfml-network.so ${LIB_DIR}/libsfml-network.so.2.3 && \
    ln -fs ${LIB_DIR}/libsfml-system.so ${LIB_DIR}/libsfml-system.so.2.3 && \
    ln -fs ${LIB_DIR}/libsfml-window.so ${LIB_DIR}/libsfml-window.so.2.3 || \
    get_out "Failed to create symbolic links"

ln -fs ${LIB_DIR}/libsfml-audio.so ${LIB_DIR}/libsfml-audio.so.2 && \
    ln -fs ${LIB_DIR}/libsfml-graphics.so ${LIB_DIR}/libsfml-graphics.so.2 && \
    ln -fs ${LIB_DIR}/libsfml-network.so ${LIB_DIR}/libsfml-network.so.2 && \
    ln -fs ${LIB_DIR}/libsfml-system.so ${LIB_DIR}/libsfml-system.so.2 && \
    ln -fs ${LIB_DIR}/libsfml-window.so ${LIB_DIR}/libsfml-window.so.2 || \
    get_out "Failed to create symbolic links"

# Conf

echo "Adding variables to your shell configuration. Do not forget to restart it after."

test_and_add_bash ~/.shrc
test_and_add_bash ~/.bashrc
test_and_add_bash ~/.kshrc
test_and_add_bash ~/.zshrc

test_and_add_csh ~/.cshrc
test_and_add_csh ~/.tcshrc

get_out "All bunnies are in!"

