#!/bin/sh
clear
echo "## ----------------------------------------------------------------------------- ##"
sleep 0.03
echo "## -- HANGED BUNNY STUDIO 2014-2024 ------- ---   -   --- ---- --  --   - --- -- ##"
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
	    echo "export LIBRARY_PATH=\"${LIB_DIR}\"" >> $1
	    echo "export C_INCLUDE_PATH=\"${INCLUDE_DIR}\"" >> $1
	    echo "export CPLUS_INCLUDE_PATH=\"${INCLUDE_DIR}\"" >> $1
	fi
    fi
}

test_and_add_csh()
{
    if [ -e $1 ] ; then
	FROOT=`grep "${INCLUDE_DIR}" $1`
	if [ -z "${FROOT}" ]; then
	    echo "" >> $1
	    echo "setenv LIBRARY_PATH \"${LIB_DIR}\"" >> $1
	    echo "setenv C_INCLUDE_PATH \"${INCLUDE_DIR}\"" >> $1
	    echo "setenv CPLUS_INCLUDE_PATH \"${INCLUDE_DIR}\"" >> $1
	fi
    fi
}

mkdir -p ${LIB_DIR} ${INCLUDE_DIR}		|| get_out "Failed to create installation directories."

make -j8					|| get_out "No bunnies were built. Make failed."

# Bunnies
cp -r include/* ${INCLUDE_DIR}			|| get_out "Failed to install Lapin headers."
cp liblapin*.a ${LIB_DIR}			|| get_out "Failed to install Lapin binaries."
rm -rf ${INCLUDE_DIR}/private
rm -f ${INCLUDE_DIR}/lapin_private.h

chmod 644 ${INCLUDE_DIR}/*.h*			|| get_out "Failed to change mode of headers."
chmod 644 ${INCLUDE_DIR}/*/*.h*			|| get_out "Failed to change mode of headers."
chmod 644 ${INCLUDE_DIR}/*/*/*.h*		|| get_out "Failed to change mode of headers."
chmod 644 ${LIB_DIR}/*.a			|| get_out "Failed to change mode of binaries."

# Conf

echo "Adding variables to your shell configuration. Do not forget to restart it after."

test_and_add_bash ~/.shrc
test_and_add_bash ~/.bashrc
test_and_add_bash ~/.kshrc
test_and_add_bash ~/.zshrc

test_and_add_csh ~/.cshrc
test_and_add_csh ~/.tcshrc

get_out "All bunnies are in!"

