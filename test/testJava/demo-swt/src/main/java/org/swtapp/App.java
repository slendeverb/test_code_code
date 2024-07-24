package org.swtapp;

import org.eclipse.swt.SWT;
import org.eclipse.swt.custom.SashForm;
import org.eclipse.swt.layout.*;
import org.eclipse.swt.widgets.*;

public class App {
    public static void main(String[] args) {
        Display display = new Display();
        Shell shell = new Shell();
        shell.setLayout(new FillLayout());
        shell.setSize(1000, 600);

        TabFolder tabFolder = new TabFolder(shell, SWT.NONE);
        TabItem tabItem = new TabItem(tabFolder, SWT.NONE);
        tabItem.setText("选项卡1");
        tabItem.setControl(createTabPage(tabFolder));

        shell.open();
        while (!shell.isDisposed()) {
            while (!display.readAndDispatch()) {
                display.sleep();
            }
        }
        shell.dispose();
    }

    private static Composite tabComposite;
    private static SashForm externalSashForm;
    private static SashForm internalSashForm;

    private static Composite rightUpComposite;
    private static Composite rightDownComposite;

    private static Group group;
    private static Composite leftComposite;

    private static GridLayout commonGridLayout;

    private static Control createTabPage(TabFolder tabFolder) {
        tabComposite = new Composite(tabFolder, SWT.NONE);
        tabComposite.setLayout(new FillLayout());

        externalSashForm = new SashForm(tabComposite, SWT.NONE);
        externalSashForm.setLayout(new FillLayout());

        createLeftBody();
        new Composite(externalSashForm, SWT.NONE);
        createRightBody();

        externalSashForm.setWeights(new int[] { 10, 1, 8 });
        return tabComposite;
    }

    private static void createRightBody() {
        internalSashForm = new SashForm(externalSashForm, SWT.VERTICAL);
        internalSashForm.setLayout(new FillLayout());

        rightUpComposite = new Composite(internalSashForm, SWT.BORDER);
        GridLayout gridLayout = new GridLayout(4, true);
        gridLayout.horizontalSpacing = 10;
        gridLayout.verticalSpacing = 20;
        rightUpComposite.setLayout(gridLayout);
        setRightUpComp();

        rightDownComposite = new Composite(internalSashForm, SWT.BORDER);
        rightDownComposite.setLayout(new FillLayout());
        setRightDownComp();

        internalSashForm.setWeights(new int[] { 2, 3 });
    }

    private static void setRightUpComp() {
        Label label1 = new Label(rightUpComposite, SWT.NONE);
        label1.setText("第一行");
        Combo combo1 = new Combo(rightUpComposite, SWT.BORDER);
        combo1.setLayoutData(new GridData(SWT.FILL, SWT.FILL, true, false, 3, 1));
        combo1.setItems(new String[] { "选项一", "选项二", "选项三" });

        Label label2 = new Label(rightUpComposite, SWT.NONE);
        label2.setText("第二行");
        List list2 = new List(rightUpComposite, SWT.BORDER);
        list2.setLayoutData(new GridData(SWT.FILL, SWT.FILL, true, false, 2, 1));
        list2.setItems(new String[] { "列表一" });
        new Text(rightUpComposite, SWT.BORDER | SWT.READ_ONLY);

        Label label3 = new Label(rightUpComposite, SWT.NONE);
        label3.setText("第三行");
        for (int i = 0; i < 3; i++) {
            new Button(rightUpComposite, SWT.CHECK).setText("按钮" + i);
            ;
        }

        Label label4 = new Label(rightUpComposite, SWT.NONE);
        label4.setText("第四行");
        Text text4 = new Text(rightUpComposite, SWT.BORDER | SWT.READ_ONLY);
        text4.setLayoutData(new GridData(SWT.FILL, SWT.FILL, true, false, 3, 1));
        text4.setText("这是SWT框架的阶段练习");
    }

    private static void setRightDownComp() {
        new Button(rightDownComposite, SWT.PUSH).setText("放个Button意思意思");
    }

    private static void createLeftBody() {
        group = new Group(externalSashForm, SWT.BORDER);
        group.setLayout(new FillLayout());
        group.setText("左侧模块");

        leftComposite = new Composite(group, SWT.NONE);
        leftComposite.setLayoutData(new GridData(SWT.FILL, SWT.FILL, true, true));

        commonGridLayout = new GridLayout();
        commonGridLayout.numColumns = 3;
        commonGridLayout.makeColumnsEqualWidth = true;
        commonGridLayout.horizontalSpacing = 40;
        commonGridLayout.verticalSpacing = 20;

        leftComposite.setLayout(commonGridLayout);

        setLeftComp();
    }

    private static void setLeftComp() {
        Button triggerSwitchButton = new Button(leftComposite, SWT.CHECK);
        triggerSwitchButton.setLayoutData(new GridData(SWT.FILL, SWT.FILL, false, false, 3, 1));
        triggerSwitchButton.setText("启动条件");

        Composite startComp = new Composite(leftComposite, SWT.NONE);
        startComp.setLayoutData(new GridData(SWT.FILL, SWT.FILL, true, false, 3, 1));
        startComp.setLayout(commonGridLayout);

        Text text1 = new Text(startComp, SWT.READ_ONLY | SWT.BORDER);
        text1.setText("swt阶段练习 启动触发条件");
        text1.setLayoutData(new GridData(SWT.FILL, SWT.FILL, true, false, 3, 1));

        Button starButton1 = new Button(startComp, SWT.RADIO);
        starButton1.setText("按键开始");
        Text startText1 = new Text(startComp, SWT.BORDER);
        startText1.setLayoutData(new GridData(SWT.FILL, SWT.FILL, true, false));
        startText1.setText("快捷键");

        new Text(startComp, SWT.NONE);

        Button startButton2 = new Button(startComp, SWT.RADIO);
        startButton2.setText("信号开始");
        Text startText2 = new Text(startComp, SWT.BORDER);
        startText2.setLayoutData(new GridData(SWT.FILL, SWT.FILL, true, false));
        Button startEditButton1 = new Button(startComp, SWT.PUSH);
        startEditButton1.setText("编辑按钮");
        startEditButton1.setLayoutData(new GridData(SWT.FILL, SWT.FILL, true, false));

        Button startButton3 = new Button(startComp, SWT.RADIO);
        startButton3.setText("变量开始");
        Text startText3 = new Text(startComp, SWT.BORDER);
        startText3.setLayoutData(new GridData(SWT.FILL, SWT.FILL, true, false));
        Button startEditButton2 = new Button(startComp, SWT.PUSH);
        startEditButton2.setText("编辑按钮");
        startEditButton2.setLayoutData(new GridData(SWT.FILL, SWT.FILL, true, false));

        Composite endComp = new Composite(leftComposite, SWT.NONE);
        endComp.setLayoutData(new GridData(SWT.FILL, SWT.FILL, true, false, 3, 1));
        endComp.setLayout(commonGridLayout);

        Text text2 = new Text(endComp, SWT.READ_ONLY | SWT.BORDER);
        text2.setText("swt阶段练习 停止触发条件");
        text2.setLayoutData(new GridData(SWT.FILL, SWT.FILL, true, false, 3, 1));

        Button endButton1 = new Button(endComp, SWT.RADIO);
        endButton1.setText("按键停止");
        Text endText1 = new Text(endComp, SWT.BORDER);
        endText1.setLayoutData(new GridData(SWT.FILL, SWT.FILL, true, false));
        endText1.setText("快捷键");

        new Text(endComp, SWT.NONE);

        Button endButton2 = new Button(endComp, SWT.RADIO);
        endButton2.setText("信号停止");
        Text endText2 = new Text(endComp, SWT.BORDER);
        endText2.setLayoutData(new GridData(SWT.FILL, SWT.FILL, true, false));
        Button endEditButton1 = new Button(endComp, SWT.PUSH);
        endEditButton1.setText("编辑按钮");
        endEditButton1.setLayoutData(new GridData(SWT.FILL, SWT.FILL, true, false));

        Button endButton3 = new Button(endComp, SWT.RADIO);
        endButton3.setText("变量停止");
        Text endText3 = new Text(endComp, SWT.BORDER);
        endText3.setLayoutData(new GridData(SWT.FILL, SWT.FILL, true, false));
        Button endEditButton2 = new Button(endComp, SWT.PUSH);
        endEditButton2.setText("编辑按钮");
        endEditButton2.setLayoutData(new GridData(SWT.FILL, SWT.FILL, true, false));
    }
}
